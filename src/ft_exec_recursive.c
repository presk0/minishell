/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2025/01/17 14:31:00 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>
void *ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
    if (new_size == 0)
    {
        free(ptr);
        return NULL;
    }
    void *new_ptr = malloc(new_size);
    if (!new_ptr)
    {
        perror("minishell: ft_realloc: malloc failed");
        return NULL;
    }
    if (ptr)
    {
        ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size);
        free(ptr);
    }
    return new_ptr;
}

void print_export(char **tab)
{
	while (*tab)
	{
		printf("declare -x%s\n", *tab++);
	}
}

char *ft_getenv(char **env, const char *var)
{
    size_t var_len = strlen(var);
    for (int i = 0; env[i] != NULL; i++)
    {
        if (strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
        {
            return env[i] + var_len + 1;
        }
    }
    return NULL;
}

int ft_exit(t_list *gc)
{
	minishell_exit(gc);
	return (0);
}

int	unset_var_in_env(t_list *gc, char *** env, char *var)
{
	int		i;
	int		j;
    size_t var_len;
	
	var_len	= strlen(var);
	i = 0;
    while ((*env)[i] != NULL)
    {
        if (ft_strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
        {
            gc_free_item(&gc, (*env)[i]);
			j = 0;
            while ((*env)[j] != NULL)
            {
                (*env)[j] = (*env)[j + 1];
				j++;
            }
            return (0);
        }
		i++;
    }
    return (1);
}

int ft_unset(t_list *gc, char ***env, t_token *token)
{
	char *var = token->args[1];

	return (unset_var_in_env(gc, env, var));
}

int is_valid_var_name(const char *var)
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

int is_var_in_env(char **env, const char *var)
{
    size_t	var_len;
	int		i;

	i = 0;	
	var_len	= strlen(var);
    while (env[i] != NULL)
    {
        if (strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
            return (TRUE);
    }
    return (FALSE);
}

int ft_setenv(t_list *gc, char ***env, char *var)
{
	char		*delimiter;

    if (var != NULL)
    {
        delimiter = ft_strchr(var, '=');
        if (!delimiter)
            return (FALSE);
		if (is_valid_var_name(var))
		{
		   	if (is_var_in_env(*env, var))
				unset_var_in_env(gc, env, var);
			append_tab(gc, env, var);
		}
    }
	return (TRUE);
}

int ft_export(t_list *gc, char ***env, t_token *token)
{
	int			i;

    if (!token->args[1])
    {
        print_export(*env);
        return (0);
    }
	i = 1;
    while (token->args[i] != NULL)
    {
		if (!ft_setenv(gc, env, token->args[i]))
			continue ;
	}
	return (0);
}

int ft_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
    {
        printf("%s\n", env[i]);
    }
	return (0);
}

char	*gc_strjoin(t_list *gc, const char *s1, const char *s2)
{
	char	*ret;

	//ret = gc_malloc(gc, sizeof(char *), ft_strlen(s1) + ft_strlen(s2) + 1)
	ret = ft_strjoin(s1, s2);
	if (!gc_append(&gc, ret))
		minishell_exit(gc);
	return (ret);
}

int ft_cd(t_list *gc, char **env, t_token *token)
{
    char *path;
    char cwd[1024];

    if (token->args[1] == NULL)
    {
        path = ft_getenv(env, "HOME");
        if (path == NULL)
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return 1;
        }
    }
    else
        path = token->args[1];
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return 1;
    }
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
		char	*env_line;

		env_line = gc_strjoin(gc, "PWD=", cwd);
		printf("%s\n", env_line);
        if (!ft_setenv(gc, &env, env_line))
        {
            fprintf(stderr, "minishell: cd: failed to update PWD\n");
            return 1;
        }
    }
    else
    {
        perror("minishell: cd: failed to get current directory");
        return 1;
    }
    return 0;
}

int	ft_echo(char **env,t_token *token)
{
	(void)env;
    int newline = TRUE;
    int i = 1;
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

void	exec_cmd(t_list *gc, t_token *tok, char **env)
{
	(void)gc;
	if (!tok)
		return ;
	handle_redir_in(tok);
	handle_redir_out(tok);
	execve(tok->cmd, tok->args, env);
	perror("[exec_cmd] execve failed");
	//minishell_exit(gc);
}

void	exec_content(t_list *gc, t_btree *node, char **env)
{
	t_btree_content *content = node->content;
	t_token *tok = &(content->token);
	exec_cmd(gc, tok, env);
}

int	exec_forking(t_list *gc, t_btree *node, char **env)
{
    pid_t pid;
	int	status;

	status = -1;
    pid = fork();
    if (pid == -1)
	{
        perror("[rec_exec] fork failed");
        minishell_exit(gc);
    }
    if (pid == 0)
	{
        exec_content(gc, node, env);
		minishell_exit(gc);
    }
    waitpid(pid, &status, 0);
	return (status);
}

void	reset_stdin(t_list *gc, int stdin_fd)
{
	if (dup2(stdin_fd, STDIN_FILENO) == -1) {
		perror("[rec_exec] dup2 failed");
		minishell_exit(gc);
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

int	ft_pwd(char **env, t_token *token)
{
	(void)token;
	printf("%s\n", ft_getenv(env,"PWD"));
	return (0);
}

int	exec_builtin(t_list *gc, t_token *token, char ***env_in)
{
	int	exit_status;
	char	**env;

	// if (apply_redirections(token, i))
	// 	ft_print_err("%s: %d: err applying redir\n", __FILE__, __LINE__);
	set_cmd_id(token);
	env = *env_in;
	exit_status = 0;
	if (token->cmd_id == (int)ECHO_ID)
		exit_status = ft_echo(env, token);
	else if (token->cmd_id == (int)CD_ID)
		exit_status = ft_cd(gc, env, token);
	else if (token->cmd_id == (int)PWD_ID)
		exit_status = ft_pwd(env, token);
	else if (token->cmd_id == (int)EXPORT_ID)
		exit_status = ft_export(gc, &env, token);
	else if (token->cmd_id == (int)UNSET_ID)
		exit_status = ft_unset(gc, &env, token);
	else if (token->cmd_id == (int)ENV_ID)
		exit_status = ft_env(env);
	else if (token->cmd_id == (int)EXIT_ID)
		exit_status = ft_exit(gc);
	// if (restore_std_fds(m->std_fds) == -1)
	// 	ft_print_err("%s: %d: err restore std fds", __FILE__, __LINE__);
	return (exit_status);
}

/* remarque du type *gc non protege assez abusive
 * Car passe par adresse
 */
int	exec_builtin_scotch(t_list **gc, t_btree *node, char ***env)
{
	(void)gc;
	(void)node;
	(void)env;
	t_btree_content	*c;
	int	ret;

	c = node->content;
	ret = exec_builtin(*gc, &c->token, env);
	return (ret);
}

int	is_builtin(t_btree_content *c)
{
	t_token	*token;

	token = &c->token;
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

//void rec_exec(t_list *gc, t_btree *node, char **env)
//{
//    int pipe_fd[2];
//    pid_t pid;
//    int status;
//    int stdin_fd;
//
//    stdin_fd = dup(STDIN_FILENO);
//    if (stdin_fd == -1)
//	{
//        perror("[rec_exec] dup failed");
//        minishell_exit(gc);
//    }
//    if (is_pipe(node))
//    {
//        if (pipe(pipe_fd) == -1) {
//            perror("[rec_exec] pipe failed");
//            minishell_exit(gc);
//        }
//        pid = fork();
//        if (pid == -1) {
//            perror("[rec_exec] fork failed");
//            minishell_exit(gc);
//        }
//        if (pid == 0) {
//            close(pipe_fd[0]);
//            dup2(pipe_fd[1], STDOUT_FILENO);
//            close(pipe_fd[1]);
//            rec_exec(gc, node->left, env);
//            minishell_exit(gc);
//        }
//        close(pipe_fd[1]);
//        dup2(pipe_fd[0], STDIN_FILENO);
//        close(pipe_fd[0]);
//        rec_exec(gc, node->right, env);
//        waitpid(pid, &status, 0);
//    }
//    else
//    {
//		if (is_builtin(node->content))
//			status = exec_builtin_scotch(&gc, node, &env);
//		else
//			status = exec_forking(gc, node, env);
//		reset_stdin(gc, stdin_fd);
//    }
//    close(stdin_fd);
//}

void handle_dup_failure(t_list *gc, int fd, const char *msg)
{
    if (fd == -1)
    {
        perror(msg);
        minishell_exit(gc);
    }
}

void handle_fork_failure(t_list *gc, pid_t pid, const char *msg)
{
    if (pid == -1)
    {
        perror(msg);
        minishell_exit(gc);
    }
}

void handle_pipe_failure(t_list *gc, int result, const char *msg)
{
    if (result == -1)
    {
        perror(msg);
        minishell_exit(gc);
    }
}

void execute_pipe_child(t_list *gc, t_btree *node, char **env, int pipe_fd[])
{
    close(pipe_fd[0]);
    dup2(pipe_fd[1], STDOUT_FILENO);
    close(pipe_fd[1]);
    rec_exec(gc, node->left, env);
    minishell_exit(gc);
}

void execute_pipe_parent(t_list *gc, t_btree *node, char **env, int pipe_fd[], pid_t pid)
{
    int status;

    close(pipe_fd[1]);
    dup2(pipe_fd[0], STDIN_FILENO);
    close(pipe_fd[0]);
    rec_exec(gc, node->right, env);
    waitpid(pid, &status, 0);
}

void execute_command(t_list *gc, t_btree *node, char **env, int stdin_fd)
{
    int status;

    if (is_builtin(node->content))
        status = exec_builtin_scotch(&gc, node, &env);
    else
        status = exec_forking(gc, node, env);
    reset_stdin(gc, stdin_fd);
}

void rec_exec(t_list *gc, t_btree *node, char **env)
{
    int pipe_fd[2];
    pid_t pid;
    int stdin_fd = dup(STDIN_FILENO);

    handle_dup_failure(gc, stdin_fd, "[rec_exec] dup failed");
    if (is_pipe(node))
    {
        handle_pipe_failure(gc, pipe(pipe_fd), "[rec_exec] pipe failed");
        pid = fork();
        handle_fork_failure(gc, pid, "[rec_exec] fork failed");
        if (pid == 0)
            execute_pipe_child(gc, node, env, pipe_fd);
        else
            execute_pipe_parent(gc, node, env, pipe_fd, pid);
    }
    else
    {
        execute_command(gc, node, env, stdin_fd);
    }
    close(stdin_fd);
}
