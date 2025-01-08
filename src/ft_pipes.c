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

int	is_pipe(t_btree *node)
{
	t_btree_content	*c;

	c = node->content;
	return (!ft_strncmp(c->cmd, "|", 1));
}

int open_redirect(char *file, int mode)
{
    int fd = open(file, mode, 0666);
    if (fd == -1) {
        perror("[open_redirect] Redirection failed");
        return (-1);
    }
    return fd;
}

void handle_redir_in(t_token *tok)
{
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

void handle_redir_out(t_token *tok)
{
	int	redir;
    int mode = tok->append_flag ? O_CREAT | O_WRONLY | O_APPEND : O_CREAT | O_WRONLY | O_TRUNC;

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

void    exec_cmd(t_list *gc, t_token *tok, char **envp)
{
    if (!tok)
        return ;
    handle_redir_in(tok);
    handle_redir_out(tok);
    execve(tok->cmd, tok->args, envp);
    perror("[exec_cmd] execve failed");
    minishell_exit(gc);
}

void    exec_content(t_list *gc, t_btree *node, char **envp)
{
    t_btree_content *content = node->content;
    t_token *tok = &(content->token);
    //tokenize_cmd(gc, content->cmd, tok);
    exec_cmd(gc, tok, envp);
}

void    tokenize_content(t_list *gc, t_btree *node, char **envp)
{
    (void)envp;
    t_btree_content *content = node->content;
    t_token *tok = &(content->token);
    tokenize_cmd(gc, content->cmd, tok);
}

//void rec_exec(t_list *gc, t_btree *node, char **envp) {
//    int pipe_fd[2];
//    pid_t pid;
//    int status;
//
//    if (!check_childs(gc, node) || !node)
//        return;
//    if (is_pipe(node))
//    {
//        if (pipe(pipe_fd) == -1)
//        {
//            perror("[rec_exec] pipe failed");
//            minishell_exit(gc);
//        }
//        pid = fork();
//        if (pid == -1)
//        {
//            perror("[rec_exec] fork failed");
//            minishell_exit(gc);
//        }
//        if (pid == 0)
//        {
//            close(pipe_fd[0]);
//            dup2(pipe_fd[1], STDOUT_FILENO);
//            close(pipe_fd[1]);
//            rec_exec(gc, node->left, envp);
//            minishell_exit(gc);
//        }
//        close(pipe_fd[1]);
//        dup2(pipe_fd[0], STDIN_FILENO);
//        close(pipe_fd[0]);
//        waitpid(pid, &status, 0);
//        rec_exec(gc, node->right, envp);
//    }
//    else
//    {
//        pid = fork();
//        if (pid == -1)
//        {
//            perror("[rec_exec] fork failed");
//            minishell_exit(gc);
//        }
//
//        if (pid == 0)
//        {
//            exec_content(gc, node, pipe_fd, envp);
//        }
//        waitpid(pid, &status, 0);
//    }
//}

void rec_exec(t_list *gc, t_btree *node, char **envp) {
    int pipe_fd[2];
    pid_t pid;
    int status;

    if (!check_childs(gc, node) || !node) // Ensure valid node
        return;

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
        if (pid == 0) { // Child process: Execute left side of the pipe
            close(pipe_fd[0]); // Close read end
            dup2(pipe_fd[1], STDOUT_FILENO); // Redirect stdout to pipe write end
            close(pipe_fd[1]); // Close write end after dup2
            rec_exec(gc, node->left, envp); // Recursively execute left side
            minishell_exit(gc); // Exit child process after execution
        }
        // Parent process: Close the write end and prepare for the right side
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipe_fd[0]); // Close read end after dup2
        waitpid(pid, &status, 0); // Wait for the child to finish
        rec_exec(gc, node->right, envp); // Recursively execute right side
    } else {
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

void    exec_tree(t_list *gc, t_btree *cmd_tree, char **envp)
{
    pid_t pid;
    int status;
	char			*sep;

    pid = fork();
    if (pid == -1) {
        perror("[exec_tree] fork failed");
        minishell_exit(gc);
    }
    if (pid == 0) {
        sep = ft_strdup("|");
        gc_append(&gc, sep);
		btree_split(gc, cmd_tree, sep);
		if (!check_childs(gc, cmd_tree)) 
			return ;
		rec_tokenization(gc, cmd_tree, NULL);
        rec_exec(gc, cmd_tree, envp);
		gc_free_tree(&gc, &cmd_tree, gc_free_node_content);
        gc_free_item(&gc, sep);
        exit(0);
    }
    waitpid(pid, &status, 0);
}