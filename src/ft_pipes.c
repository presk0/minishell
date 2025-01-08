/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   template.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/09/05 14:15:32 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
int open_redirect(char *file, int mode)
{
    int fd = open(file, mode, 0666);
    if (fd == -1) {
        perror("[open_redirect] Redirection failed");
        return (-1);
    }
    return fd;
}

void handle_redir_in(t_token *tok, int p[2])
{
	(void)p;
	int	redir;
    int mode = O_RDONLY;

    if (tok->redir_in && !tok->heredoc)
	{
		redir = open_redirect(tok->redir_in, mode);
		if (redir != -1)
		{
			dup2(redir, STDIN_FILENO);
			close(redir);
		}
	}
}

void handle_redir_out(t_token *tok, int p[2])
{
	int	redir;
    int mode = tok->append_flag ? O_CREAT | O_WRONLY | O_APPEND : O_CREAT | O_WRONLY | O_TRUNC;
	(void)p;

    if (tok->redir_out)
	{
		redir = open_redirect(tok->redir_out, mode);
		if (redir != -1)
		{
			dup2(redir, STDOUT_FILENO);
			close(redir);
		}
	}
}

int	is_pipe(t_btree *node)
{
	t_btree_content	*c;

	c = node->content;
	return (!ft_strncmp(c->cmd, "|", 1));
}

void    exec_cmd(t_list *gc, t_token *tok, int p[2], char **envp)
{
	(void)p;
    if (!tok)
        return ;
    handle_redir_in(tok, p);
    handle_redir_out(tok, p);
    execve(tok->cmd, tok->args, envp);
    perror("[exec_cmd] execve failed");
    minishell_exit(gc);
}

void    exec_content(t_list *gc, t_btree *node, int p[2], char **envp)
{
    t_btree_content *content = node->content;
    t_token *tok = &(content->token);
    //tokenize_cmd(gc, content->cmd, tok);
    exec_cmd(gc, tok, p, envp);
}

void    tokenize_content(t_list *gc, t_btree *node, char **envp)
{
    (void)envp;
    t_btree_content *content = node->content;
    t_token *tok = &(content->token);
    tokenize_cmd(gc, content->cmd, tok);
}

void rec_exec(t_list *gc, t_btree *node, char **envp) {
    int pipe_fd[2];
    pid_t pid;
    int status;

    if (!check_childs(gc, node) || !node)
        return;
    if (is_pipe(node))
    {
        if (pipe(pipe_fd) == -1)
        {
            perror("[rec_exec] pipe failed");
            minishell_exit(gc);
        }
        pid = fork();
        if (pid == -1)
        {
            perror("[rec_exec] fork failed");
            minishell_exit(gc);
        }
        if (pid == 0)
        {
            close(pipe_fd[0]);
            dup2(pipe_fd[1], STDOUT_FILENO);
            close(pipe_fd[1]);
            rec_exec(gc, node->left, envp);
            minishell_exit(gc);
        }
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        waitpid(pid, &status, 0);
        rec_exec(gc, node->right, envp);
    }
    else
    {
        pid = fork();
        if (pid == -1)
        {
            perror("[rec_exec] fork failed");
            minishell_exit(gc);
        }

        if (pid == 0)
        {
            exec_content(gc, node, pipe_fd, envp);
        }
        waitpid(pid, &status, 0);
    }
}

void rec_tokenization(t_list *gc, t_btree *node, char **envp)
{
    if (!node)
        return;
    if (is_pipe(node))
    {
        rec_tokenization(gc, node->left, envp);   // Continue le traitement
        rec_tokenization(gc, node->right, envp);      // Continue le traitement
    }
    else
        tokenize_content(gc, node, envp);
}