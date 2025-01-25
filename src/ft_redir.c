/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/26 00:54:04 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int handle_heredoc(char *delimiter);

int	open_redirect(char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0666);
	if (fd == -1)
	{
		perror("[open_redirect] Redirection failed");
		return (-1);
	}
	return (fd);
}

void	handle_redir_in(t_token *tok)
{
	int	redir;
	int	mode;

	mode = O_RDONLY;
	if (tok->redir_in && !tok->heredoc)
	{
		redir = open_redirect(tok->redir_in, mode);
		if (redir != -1)
		{
			dup2(redir, STDIN_FILENO);
			close(redir);
		}
	}
	else if (tok->heredoc)
	{
		// Appeler la fonction de gestion du heredoc
		if (handle_heredoc(tok->redir_in) == -1)
		{
			fprintf(stderr, "Error: Failed to handle heredoc\n");
		}
	}
}

int handle_heredoc(char *delimiter)
{
	int pipe_fd[2];
	char *line = NULL;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return -1;
	}
	while (1)
	{
		// Afficher un prompt
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
		{
			perror("get_next_line");
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			return -1;
		}
		size_t len = strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		write(pipe_fd[1], line, len);
		write(pipe_fd[1], "\n", 1); // Restaurer le newline
		free(line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(pipe_fd[0]);
		return -1;
	}
	close(pipe_fd[0]);
	return 0;
}

void	handle_redir_out(t_token *tok)
{
	int	redir;
	int	mode;

	mode = tok->append_flag ? O_CREAT | O_WRONLY | O_APPEND : O_CREAT | O_WRONLY | O_TRUNC;
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

char *read_heredoc(char *delimiter) {

    char *input = NULL;

    char *line = NULL;

    size_t total_length = 0;


    printf("Enter text (end with '%s'):\n", delimiter);


    while (1) {

        // Use readline to get a line of input

        line = readline("> "); // Prompt for input

        if (line == NULL) {

            break; // Break on EOF or error

        }


        // Check if the line matches the delimiter

        if (strcmp(line, delimiter) == 0) {

            free(line); // Free the line before breaking

            break; // Exit if the delimiter is found

        }


        // Remove the newline character from the line

        line[strcspn(line, "\n")] = 0;


        // Allocate or reallocate memory for the input

        char *new_input = realloc(input, total_length + strlen(line) + 1);

        if (new_input == NULL) {

            free(input); // Free previous memory on failure

            free(line); // Free the line

            perror("Memory allocation failed");

            return NULL;

        }

        input = new_input;


        // Copy the line to the input

        strcpy(input + total_length, line);

        total_length += strlen(line);


        free(line); // Free the line after copying

    }


    return input; // Return the collected input

}
