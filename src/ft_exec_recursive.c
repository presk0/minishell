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
void	print_export(char **tab)
{
	while (*tab)
	{
		printf("declare -x%s\n", *tab++);
	}
}

char	*ft_getenv(const char *var)
{
	size_t	var_len;

	var_len = strlen(var);
	for (int i = 0; d.env[i] != NULL; i++)
	{
		if (strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
		{
			return (d.env[i] + var_len + 1);
		}
	}
	return (NULL);
}

int	ft_exit()
{
	minishell_exit("exit\n", 0);
	return (0);
}

int	unset_var_in_env(char *var)
{
	int		i;
	int		j;
	size_t	var_len;

	var_len = strlen(var);
	i = 0;
	while (d.env[i] != NULL)
	{
		if (ft_strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
		{
			gc_free_item(&d.gc, d.env[i]);
			j = 0;
			while (d.env[j] != NULL)
			{
				d.env[j] = d.env[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_token *token)
{
	char	*var;

	var = token->args[1];
	return (unset_var_in_env(var));
}




int	ft_setenv(char *var)
{
	char	*delimiter;

	if (var != NULL)
	{
		delimiter = ft_strchr(var, '=');
		if (!delimiter)
			return (FALSE);
		if (ft_varlen(var))
		{
			if (is_var_in_env(var))
				unset_var_in_env(var);
			append_tab(&d.env, var);
		}
	}
	return (TRUE);
}

int	ft_export(t_token *token)
{
	int	i;

	if (!token->args[1])
	{
		print_export(d.env);
		return (0);
	}
	i = 1;
	while (token->args[i] != NULL)
	{
		if (!ft_setenv(token->args[i]))
			continue ;
	}
	return (0);
}

int	ft_env()
{
	for (int i = 0; d.env[i] != NULL; i++)
	{
		printf("%s\n", d.env[i]);
	}
	return (0);
}


int	ft_cd(t_token *token)
{
	char	*path;
	char	cwd[1024];
	char	*env_line;

	if (token->args[1] == NULL)
	{
		path = ft_getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = token->args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		env_line = gc_strjoin("PWD=", cwd);
		printf("%s\n", env_line);
		if (!ft_setenv(env_line))
		{
			fprintf(stderr, "minishell: cd: failed to update PWD\n");
			return (1);
		}
	}
	else
	{
		perror("minishell: cd: failed to get current directory");
		return (1);
	}
	return (0);
}

int	ft_echo(t_token *token)
{
	int	newline;
	int	i;

	newline = TRUE;
	i = 1;
	if (token->args[1] != NULL && strcmp(token->args[1], "-n") == 0)
	{
		newline = FALSE;
		i++;
	}
	while (token->args[i] != NULL)
	{
		write(STDOUT_FILENO, token->args[i], strlen(token->args[i]));
		if (token->args[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
	{
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}


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

int	exec_forking(t_btree *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("[rec_exec] fork failed");
		minishell_exit("exec_forking", -1);
	}
	if (pid == 0)
	{
		reset_signals();
		exec_content(node);
		minishell_exit("exec_forking", -1);
	}
	waitpid(pid, &d.status, 0);
	return (d.status);
}

void	reset_stdin(int stdin_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1)
	{
		perror("[rec_exec] dup2 failed");
		minishell_exit("reset_stdin", -1);
	}
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

/*
*/
int	exec_builtin(t_token *token)
{
	int		exit_status;

	// if (apply_redirections(token, i))
	// 	ft_print_err("%s: %d: err applying redir\n", __FILE__, __LINE__);
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
	// if (restore_std_fds(m->std_fds) == -1)
	// 	ft_print_err("%s: %d: err restore std fds", __FILE__, __LINE__);
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


void	execute_pipe_child(t_btree *node, int pipe_fd[])
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

void	execute_command(t_btree *node, int stdin_fd)
{
	(void)stdin_fd;
	if (is_builtin(node->content))
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
