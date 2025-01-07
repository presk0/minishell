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
        perror("Redirection failed");
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
    int mode = tok->append_flag ? O_CREAT | O_WRONLY | O_APPEND : O_CREAT | O_WRONLY;
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
    t_token *tok = tokenize_cmd(gc, content->cmd);
    exec_cmd(gc, tok, p, envp);
}

void recursive_parsing(t_list *gc, t_btree *node, char **envp) {
    int pipe_fd[2];
    pid_t pid;
    int status;

    if (!node)
        return;
    if (is_pipe(node)) {
        if (pipe(pipe_fd) == -1) {
            perror("[recursive_parsing] pipe failed");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("[recursive_parsing] fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            close(pipe_fd[0]);                     // Ferme la lecture du pipe
            dup2(pipe_fd[1], STDOUT_FILENO);       // Redirige stdout vers le pipe
            close(pipe_fd[1]);                     // Ferme après duplication
            recursive_parsing(gc, node->left, envp);   // Continue le traitement
            exit(EXIT_SUCCESS);                    // Terminaison propre
        }

        close(pipe_fd[1]);                         // Ferme l'écriture du pipe
        dup2(pipe_fd[0], STDIN_FILENO);            // Redirige stdin depuis le pipe
        close(pipe_fd[0]);                         // Ferme après duplication
        waitpid(pid, &status, 0);                  // Attend la fin du sous-arbre gauche
        recursive_parsing(gc, node->right, envp);      // Continue le traitement
    } else {
        pid = fork();
        if (pid == -1) {
            perror("[recursive_parsing] fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            exec_content(gc, node, pipe_fd, envp);
        }
        waitpid(pid, &status, 0);
    }
}
