/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2025/01/16 17:27:12 by nidionis         ###   ########.fr       */
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

int ft_setenv(char ***env, const char *var, const char *value)
{
    size_t var_len = strlen(var);
    size_t value_len = strlen(value);
    char *new_entry = malloc(var_len + value_len + 2); // +2 pour '=' et '\0'
    if (!new_entry)
    {
        perror("minishell: ft_setenv: malloc failed");
        return 1;
    }
    sprintf(new_entry, "%s=%s", var, value);
    for (int i = 0; (*env)[i] != NULL; i++)
    {
        if (strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
        {
            free((*env)[i]);
            (*env)[i] = new_entry;
            return 0;
        }
    }
    // Si la variable n'existe pas encore, l'ajouter
    int env_size;
    for (env_size = 0; (*env)[env_size] != NULL; env_size++);
    char **new_env = ft_realloc(*env, env_size * sizeof(char *), (env_size + 2) * sizeof(char *)); // +2 pour la nouvelle entrée et NULL
    if (!new_env)
    {
        perror("minishell: ft_setenv: realloc failed");
        free(new_entry);
        return 1;
    }
    new_env[env_size] = new_entry;
    new_env[env_size + 1] = NULL;
    *env = new_env;
    return 0;
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

int ft_unset(char ***env, t_token *token)
{
	char *var = token->args[1];

    size_t var_len = strlen(var);
    for (int i = 0; (*env)[i] != NULL; i++)
    {
        if (strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
        {
            free((*env)[i]);
            for (int j = i; (*env)[j] != NULL; j++)
            {
                (*env)[j] = (*env)[j + 1];
            }
            return 0;
        }
    }
    return 1; // Variable non trouvée
}

int ft_export(char ***env, t_token *token)
{
    if (!token->args[1])
    {
        print_export(*env);
        return (0);
    }
    for (int i = 1; token->args[i] != NULL; i++)
    {
        char *delimiter = strchr(token->args[i], '=');
        if (!delimiter)
        {
            fprintf(stderr, "minishell: export: `%s`: not a valid identifier\n", token->args[i]);
            continue;
        }
        size_t var_len = delimiter - token->args[i];
        char var[var_len + 1];
        strncpy(var, token->args[i], var_len);
        var[var_len] = '\0';
        const char *value = delimiter + 1;
        if (ft_setenv(env, var, value) != 0)
        {
            fprintf(stderr, "minishell: export: failed to set variable\n");
			return (1);
        }
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

int ft_cd(char **env, t_token *token)
{
    char *path;

    // Vérifier si un argument est fourni
    if (token->args[1] == NULL)
    {
        // Si aucun argument, utiliser la variable d'environnement HOME
        path = ft_getenv(env, "HOME");
        if (path == NULL)
        {
            fprintf(stderr, "minishell: cd: HOME not set\n");
            return 1;
        }
    }
    else
    {
        // Utiliser le premier argument comme chemin
        path = token->args[1];
    }
    // Tenter de changer de répertoire
    if (chdir(path) != 0)
    {
        perror("minishell: cd");
        return 1;
    }
    // Mettre à jour la variable d'environnement PWD
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if (ft_setenv(&env, "PWD", cwd) != 0)
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
    int newline = TRUE; // Par défaut, on ajoute une nouvelle ligne
    int i = 1; // Commencer à 1 pour ignorer le premier argument (la commande elle-même)
    if (token->args[1] != NULL && strcmp(token->args[1], "-n") == 0)
    {
        newline = FALSE; // Ne pas ajouter de nouvelle ligne
        i++; // Passer à l'argument suivant
    }
    while (token->args[i] != NULL)
    {
        write(STDOUT_FILENO, token->args[i], strlen(token->args[i]));
        if (token->args[i + 1] != NULL) // Si ce n'est pas le dernier argument
            write(STDOUT_FILENO, " ", 1); // Ajouter un espace
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
		exit_status = ft_cd(env, token);
	else if (token->cmd_id == (int)PWD_ID)
		exit_status = ft_pwd(env, token);
	else if (token->cmd_id == (int)EXPORT_ID)
		exit_status = ft_export(&env, token);
	else if (token->cmd_id == (int)UNSET_ID)
		exit_status = ft_unset(&env, token);
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

void rec_exec(t_list *gc, t_btree *node, char **env)
{
    int pipe_fd[2];
    pid_t pid;
    int status;
    int stdin_fd;

    stdin_fd = dup(STDIN_FILENO);
    if (stdin_fd == -1)
	{
        perror("[rec_exec] dup failed");
        minishell_exit(gc);
    }
    if (is_pipe(node))
    {
        if (pipe(pipe_fd) == -1) {
            perror("[rec_exec] pipe failed");
            minishell_exit(gc);
        }
        pid = fork();
        if (pid == -1) {
            perror("[rec_exec] fork failed");
            minishell_exit(gc);
        }
        if (pid == 0) {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
            rec_exec(gc, node->left, env);
            minishell_exit(gc);
        }
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        rec_exec(gc, node->right, env);
        waitpid(pid, &status, 0);
    }
    else
    {
		if (is_builtin(node->content))
			status = exec_builtin_scotch(&gc, node, &env);
		else
			status = exec_forking(gc, node, env);
		reset_stdin(gc, stdin_fd);
    }
    close(stdin_fd);
}

