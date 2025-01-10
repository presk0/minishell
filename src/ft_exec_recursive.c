/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   template.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2024/09/05 14:15:32 by nidionis		 ###   ########.fr	   */
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

//void rec_exec(t_list *gc, t_btree *node, t_env *envp)
//{
//	int pipe_fd[2];
//	pid_t pid;
//	int status;
//
//	if (!check_childs(gc, node) || !node)
//		return ;
//	if (is_pipe(node))
//	{
//		if (pipe(pipe_fd) == -1) {
//			perror("[rec_exec] pipe failed");
//			minishell_exit(gc);
//		}
//		pid = fork();
//		if (pid == -1)
//		{
//			perror("[rec_exec] fork failed");
//			minishell_exit(gc);
//		}
//		if (pid == 0)
//		{
//			close(pipe_fd[0]);
//			dup2(pipe_fd[1], STDOUT_FILENO);
//			close(pipe_fd[1]);
//			rec_exec(gc, node->left, envp);
//			minishell_exit(gc);
//		}
//		close(pipe_fd[1]);
//		dup2(pipe_fd[0], STDIN_FILENO);
//		close(pipe_fd[0]);
//		waitpid(pid, &status, 0);
//		rec_exec(gc, node->right, envp);
//	} else {
//		pid = fork();
//		if (pid == -1) {
//			perror("[rec_exec] fork failed");
//			minishell_exit(gc);
//		}
//		if (pid == 0) {
//			exec_content(gc, node, envp);
//			exit(-42);
//			//minishell_exit(gc);
//		}
//		waitpid(pid, &status, 0);
//	}
//}

void rec_exec(t_list *gc, t_btree *node, t_env *envp)
{
    int pipe_fd[2];
    pid_t pid;
    int status;
    int stdin_fd; // To save the original stdin

    stdin_fd = dup(STDIN_FILENO);
    if (stdin_fd == -1) {
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
            rec_exec(gc, node->left, envp);
            minishell_exit(gc);
        }

        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        rec_exec(gc, node->right, envp);
        waitpid(pid, &status, 0);
    }
    else
    {
        pid = fork();
        if (pid == -1) {
            perror("[rec_exec] fork failed");
            minishell_exit(gc);
        }

        if (pid == 0) {
            exec_content(gc, node, envp);
			minishell_exit(gc);
        }

        waitpid(pid, &status, 0);
    }
    if (dup2(stdin_fd, STDIN_FILENO) == -1) {
        perror("[rec_exec] dup2 failed");
        minishell_exit(gc);
    }
    close(stdin_fd);
}

