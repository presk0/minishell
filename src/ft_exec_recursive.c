/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 14:02:52 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	exec_cmd(t_token *tok)
{
	if (!tok)
		return ;
	handle_redir_in(tok);
	handle_redir_out(tok);
	execve(tok->cmd, tok->args, d.env);
	minishell_exit("[exec_cmd] execve failed", -1);
}

void	exec_content(t_btree *node)
{
	t_btree_content	*content;
	t_token			*tok;

	content = node->content;
	tok = &(content->token);
	exec_cmd(tok);
}

int	exec_forking(t_btree *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		minishell_exit("[exec_forking]", -1);
	if (pid == 0)
	{
		reset_signals();
		exec_content(node);
		minishell_exit("[exec_forking]", -1);
	}
	waitpid(pid, &d.status, 0);
	return (d.status);
}

void	reset_stdin(int stdin_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		minishell_exit("reset_stdin", -1);
}

void	pipe_left(t_btree *node, int pipe_fd[])
{
	(void)pipe_fd;
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	rec_exec(node->left);
}

void	pipe_right(t_btree *node, int pipe_fd[])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	rec_exec(node->right);
}

void	execute_command(t_btree *node, int stdin_fd)
{
	(void)stdin_fd;
	t_token	*token;

	token = &((t_btree_content *)node->content)->token;
	if (is_builtin(token))
		exec_builtin_scotch(node);
	else
		exec_forking(node);
	//reset_stdin(stdin_fd);
	//close(stdin_fd);
}

/*
void	rec_exec(t_btree *node)
{
	int		pipe_fd[2];
	int		stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	handle_dup_failure(stdin_fd, "[rec_exec] dup failed");
	if (is_pipe(node))
	{
		handle_pipe_failure(pipe(pipe_fd), "[rec_exec] pipe failed");
		pipe_left(node,  pipe_fd);
		pipe_right(node,  pipe_fd);
	}
	else
		execute_command(node,  stdin_fd);
	reset_stdin(stdin_fd);
	close(stdin_fd);
	//reset_stdin(stdin_fd);
}
*/

void	rec_exec(t_btree *node)
{
	int		pipe_fd[2];
	int		stdin_fd;
	pid_t	pid;

	stdin_fd = dup(STDIN_FILENO);
	handle_dup_failure(stdin_fd, "[rec_exec] dup failed");

	if (is_pipe(node))
	{
		handle_pipe_failure(pipe(pipe_fd), "[rec_exec] pipe failed");

		// Fork for the left side of the pipe
		pid = fork();
		if (pid == -1)
			minishell_exit("[rec_exec] fork failed", -1);
		if (pid == 0)
		{
			close(pipe_fd[0]); // Close read end
			dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
			close(pipe_fd[1]); // Close write end
			rec_exec(node->left);
			minishell_exit("[rec_exec] pipe left execution failed", -1);
		}

		// Parent process handles the right side
		close(pipe_fd[1]); // Close write end
		dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe read end
		close(pipe_fd[0]); // Close read end
		rec_exec(node->right);

		waitpid(pid, NULL, 0); // Wait for left side process to finish
	}
	else
	{
		execute_command(node, stdin_fd);
	}

	reset_stdin(stdin_fd);
	close(stdin_fd);
}
