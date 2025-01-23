/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 00:32:59 by nidionis         ###   ########.fr       */
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
	perror("[exec_cmd] execve failed");
	// minishell_exit();
}

void	exec_content(t_btree *node)
{
	t_btree_content	*content;
	t_token			*tok;

	content = node->content;
	tok = &(content->token);
	exec_cmd(tok);
}

int exec_forking(t_btree *node)

{
    pid_t pid;
    int pipe_fd[2];

    if (is_pipe(node))
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("[rec_exec] pipe failed");
            return -1;
        }
    }
    pid = fork();
    if (pid == -1)
    {
        perror("[rec_exec] fork failed");
        minishell_exit("exec_forking", -1);
    }
    if (pid == 0)
    {
        if (is_pipe(node))
        {
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
        }
        reset_signals();
        exec_content(node);
        minishell_exit("exec_forking", -1);
    }
    if (is_pipe(node))
        close(pipe_fd[1]);
    waitpid(pid, &d.status, 0);
    return d.status;
}


/*
int	exec_forking(t_btree *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("[rec_exec] fork failed");
		minishell_exit();
	}
	if (pid == 0)
	{
		reset_signals();
		exec_content(node);
		minishell_exit();
	}
	waitpid(pid, &d.status, 0);
	return (d.status);
}
*/

void	reset_stdin(int stdin_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
	{
		perror("[reset_stdin] dup2 failed");
		minishell_exit("reset_stdin", -1);
	}
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
	if (is_builtin(node->content))
		exec_builtin_scotch(node);
	else
		exec_forking(node);
	reset_stdin(stdin_fd);
	close(stdin_fd);
}

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
	//reset_stdin(stdin_fd);
}
