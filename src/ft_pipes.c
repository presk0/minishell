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
    int fd = open(file, mode);
    if (fd == -1) {
        perror("Redirection failed");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void handle_redir_in(t_token *tok)
{
    if (tok->redir_in && !tok->heredoc)
        dup2(open_redirect(tok->redir_in, O_RDONLY), STDIN_FILENO);
}

void handle_redir_out(t_token *tok)
{
    int mode = tok->append_flag ? O_CREAT | O_RDWR | O_APPEND : O_CREAT | O_RDWR | O_TRUNC;
    if (tok->redir_out)
        dup2(open_redirect(tok->redir_out, mode), STDOUT_FILENO);
}

void exec_cmd(t_list *gc, t_token *tok, int p[2], char **envp)
{
    handle_redir_in(tok);
    handle_redir_out(tok);
    if (p) {  // Handle piping if pipe file descriptors are provided
        if (p[1] != STDOUT_FILENO) dup2(p[1], STDOUT_FILENO);
        if (p[0] != STDIN_FILENO) dup2(p[0], STDIN_FILENO);
    }
    execve(tok->cmd, tok->args, envp);
    perror("[exec_cmd] execve failed");
    minishell_exit(gc);
}

void process_pipe(t_list *gc, t_token *pipe_left, t_token *pipe_right)
{
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (pid1 == 0) {
        close(pipe_fd[0]);
        exec_cmd(gc, pipe_left, pipe_fd, NULL);
    } else {
        pid_t pid2 = fork();
        if (pid2 == 0) {
            close(pipe_fd[1]);
            exec_cmd(gc, pipe_right, pipe_fd, NULL);
        } else {
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }
}
