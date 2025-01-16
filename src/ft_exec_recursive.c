/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2025/01/16 14:04:46 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	exec_cmd(t_list *gc, t_token *tok, t_env *env)
{
	(void)gc;
	if (!tok)
		return ;
	handle_redir_in(tok);
	handle_redir_out(tok);
	execve(tok->cmd, tok->args, env->my_env);
	perror("[exec_cmd] execve failed");
	//minishell_exit(gc);
}

void	exec_content(t_list *gc, t_btree *node, t_env *env)
{
	t_btree_content *content = node->content;
	t_token *tok = &(content->token);
	exec_cmd(gc, tok, env);
}

int	exec_forking(t_list *gc, t_btree *node, t_env *env)
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

/* remarque du type *gc non protege assez abusive
 * Car passe par adresse
 */
int	exec_builtin_scotch(t_list **gc, t_btree *node, t_env **env)
{
	t_data data;

	data.gc = *gc;
	data.tree = node;
	(void)env;
	return (0);
}

int	is_builtin(t_btree_content *c)
{
	(void)c;
	return (0);
}


void rec_exec(t_list *gc, t_btree *node, t_env *env)
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

