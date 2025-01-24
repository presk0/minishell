/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/23 23:14:58 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	*gc_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = gc_malloc(&d.gc, 1, new_size);
	if (!new_ptr)
	{
		perror("minishell: ft_realloc: malloc failed");
		return (NULL);
	}
	if (ptr)
	{
		if (new_size < old_size)
			new_size = old_size;
		ft_memcpy(new_ptr, ptr, new_size);
		gc_free_item(&d.gc, ptr);
	}
	return (new_ptr);
}



int	ft_varlen(const char *var)
{
	int	len;

	if (!var || !isalpha(var[0]))
		return (0);
	len = 1;
	while (var[len] != '\0')
	{
		if (!isalnum(var[len]) || var[len] == '_')
			break ;
		len++;
	}
	return (len);
}

int	is_valid_var_name(const char *var)
{
	int	i;

	i = 1;
	if (!var || !isalpha(var[0]))
		return (FALSE);
	while (var[i] != '\0')
	{
		if (!isalnum(var[i]) && var[i] != '_')
			return (FALSE);
		if (var[i] == '=')
			break ;
		i++;
	}
	return (TRUE);
}

int	is_var_in_env(const char *var)
{
	size_t	var_len;
	int		i;

	i = 0;
	var_len = strlen(var);
	while (d.env[i] != NULL)
	{
		if (strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
			return (TRUE);
	}
	return (FALSE);
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

char	*gc_strjoin(const char *s1, const char *s2)
{
	char	*ret;

	// ret = gc_malloc(sizeof(char *), ft_strlen(s1) + ft_strlen(s2) + 1)
	ret = ft_strjoin(s1, s2);
	if (!gc_append(&d.gc, ret))
		minishell_exit("[error]", -1);
	return (ret);
}


void reset_signals()
{
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
        perror("Erreur lors de la réinitialisation de SIGINT");
    if (signal(SIGTERM, SIG_DFL) == SIG_ERR)
        perror("Erreur lors de la réinitialisation de SIGTERM");
}

void	exec_cmd(t_token *tok)
{
	if (!tok)
		return ;
	handle_redir_in(tok);
	handle_redir_out(tok);
	reset_signals();
	execve(tok->cmd, tok->args, d.env);
	perror("[exec_cmd] execve failed");
	// minishell_exit("error", -1);
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
		minishell_exit("[exec_forking]", -1);
	}
	if (pid == 0)
	{
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

void	handle_dup_failure(int fd, const char *msg)
{
	if (fd == -1)
	{
		perror(msg);
		minishell_exit("handle_dup_failure", -1);
	}
}

void	handle_fork_failure(pid_t pid, const char *msg)
{
	if (pid == -1)
	{
		perror(msg);
		minishell_exit("handle_fork_failure", -1);
	}
}

void	handle_pipe_failure(int result, const char *msg)
{
	if (result == -1)
	{
		perror(msg);
		minishell_exit("handle_pipe_failure", -1);
	}
}

void	execute_pipe_child(t_btree *node, int pipe_fd[])
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[1]);
	rec_exec(node->left);
	minishell_exit("execute_pipe_child", -1);
}

void	execute_pipe_parent(t_btree *node, int pipe_fd[], pid_t pid)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	rec_exec(node->right);
	wait_for_child(pid);
}

void	execute_command(t_btree *node, int stdin_fd)
{
	t_token	*token;

	token = &((t_btree_content *)node->content)->token;
	if (is_builtin(node->content))
		exec_builtin_scotch(node);
	else
		exec_forking(node);
	reset_stdin(stdin_fd);
}

size_t	var_len(char *var)
{
	size_t	len;

	len = 0;
	if (var[len] && ft_isalnum(var[len]))
		len++;
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	return (len);
}

void	rec_exec(t_btree *node)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	handle_dup_failure(stdin_fd, "[rec_exec] dup failed");
	if (is_pipe(node))
	{
		handle_pipe_failure(pipe(pipe_fd), "[rec_exec] pipe failed");
		pid = fork();
		handle_fork_failure(pid, "[rec_exec] fork failed");
		if (pid == 0)
			execute_pipe_child(node,  pipe_fd);
		else
			execute_pipe_parent(node,  pipe_fd, pid);
	}
	else
		execute_command(node,  stdin_fd);
	dup2(stdin_fd, STDIN_FILENO);
	close(stdin_fd);
}
