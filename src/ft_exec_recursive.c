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


void	execve_node(t_btree *node)
{
	t_btree_content	*content;
	t_token			*token;

	if (!node)
		return ;
	content = node->content;
	token = &(content->token);
	reset_signals();
	execve(token->cmd, token->args, g_d.env);
	minishell_exit(token->cmd, CMD_NOT_FOUND);
}

int	exec_forking(t_btree *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		minishell_exit("[exec_forking] fork failed", -1);
	if (pid == 0)
		execve_node(node);
	waitpid(pid, &g_d.status, 0);
	return (g_d.status);
}

void	reset_stdin(int stdin_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
		minishell_exit("[rec_exec] dup2 failed", -1);
}

void	set_cmd_id(t_token *token)
{
	if (ft_strcmp(token->cmd, "echo") == 0)
		token->cmd_id = (int)ECHO_ID;
	else if (ft_strcmp(token->cmd, "cd") == 0)
		token->cmd_id = (int)CD_ID;
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		token->cmd_id = (int)PWD_ID;
	else if (ft_strcmp(token->cmd, "export") == 0)
		token->cmd_id = (int)EXPORT_ID;
	else if (ft_strcmp(token->cmd, "unset") == 0)
		token->cmd_id = (int)UNSET_ID;
	else if (ft_strcmp(token->cmd, "env") == 0)
		token->cmd_id = (int)ENV_ID;
	else if (ft_strcmp(token->cmd, "exit") == 0)
		token->cmd_id = (int)EXIT_ID;
	else
		token->cmd_id = 0;
}

int	ft_pwd(t_token *token)
{
	(void)token;
	printf("%s\n", ft_getenv("PWD"));
	return (0);
}

int	exec_builtin(t_token *token)
{
	int	exit_status;

	set_cmd_id(token);
	exit_status = 0;
	if (token->cmd_id == (int)ECHO_ID)
		exit_status = ft_echo(token);
	else if (token->cmd_id == (int)CD_ID)
		exit_status = ft_cd(token);
	else if (token->cmd_id == (int)PWD_ID)
		exit_status = ft_pwd(token);
	else if (token->cmd_id == (int)EXPORT_ID)
		exit_status = ft_export(token);
	else if (token->cmd_id == (int)UNSET_ID)
		exit_status = ft_unset(token);
	else if (token->cmd_id == (int)ENV_ID)
		exit_status = ft_env();
	else if (token->cmd_id == (int)EXIT_ID)
		exit_status = ft_exit();
	return (exit_status);
}

int	exec_builtin_scotch(t_btree *node)
{
	t_btree_content	*c;
	int				ret;

	(void)node;
	c = node->content;
	ret = exec_builtin(&c->token);
	return (ret);
}

int	is_builtin(t_token *token)
{
	if (ft_strcmp(token->cmd, "echo") == 0)
		return (ECHO_ID);
	else if (ft_strcmp(token->cmd, "cd") == 0)
		return (CD_ID);
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		return (PWD_ID);
	else if (ft_strcmp(token->cmd, "export") == 0)
		return (EXPORT_ID);
	else if (ft_strcmp(token->cmd, "unset") == 0)
		return (UNSET_ID);
	else if (ft_strcmp(token->cmd, "env") == 0)
		return (ENV_ID);
	else if (ft_strcmp(token->cmd, "exit") == 0)
		return (EXIT_ID);
	return (0);
}

void	pipe_left(t_btree *node, int pipe_fd[])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	rec_exec(node->left);
	minishell_exit("execute_pipe_child", -1);
}

void	pipe_right(t_btree *node, int pipe_fd[])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	rec_exec(node->right);
}

void	save_stds(int *saved_std)
{
	saved_std[IN] = dup(STDIN_FILENO);
	saved_std[OUT] = dup(STDOUT_FILENO);
	saved_std[ERR] = dup(STDERR_FILENO);
	handle_dup_failure(saved_std[IN], "[execute_command] dup failed");
	handle_dup_failure(saved_std[OUT], "[execute_command] dup failed");
	handle_dup_failure(saved_std[ERR], "[execute_command] dup failed");
}

void	restore_stds(int *saved_std)
{
	dup2(saved_std[IN], STDIN_FILENO);
	dup2(saved_std[OUT], STDOUT_FILENO);
	dup2(saved_std[ERR], STDERR_FILENO);
	close(saved_std[IN]);
	close(saved_std[OUT]);
	close(saved_std[ERR]);
}

void	execute_command(t_btree *node)
{
	t_token	*tok;
	int		saved_std[3];

	tok = &(((t_btree_content *)(node->content))->token);
	save_stds(saved_std);
	handle_redir_in(tok);
	handle_redir_out(tok);
	if (is_builtin(tok))
		exec_builtin_scotch(node);
	else
		exec_forking(node);
	restore_stds(saved_std);
}

void	rec_exec(t_btree *node)
{
	int pipe_fd[2];
	int stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	handle_dup_failure(stdin_fd, "[rec_exec] dup failed");
	if (is_pipe(node))
	{
		handle_pipe_failure(pipe(pipe_fd), "[rec_exec] pipe failed");
		if (fork() == 0)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			rec_exec(node->left);
			exit(EXIT_SUCCESS);
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		rec_exec(node->right);
	}
	else
		execute_command(node);
	reset_stdin(stdin_fd);
	close(stdin_fd);
}