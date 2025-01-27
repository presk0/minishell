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

int			handle_heredoc(char *delimiter);

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
		if (handle_heredoc(tok->redir_in) == -1)
			fprintf(stderr, "Error: Failed to handle heredoc\n");
	}
}

int	handle_eoheredoc(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (-1);
}

/*
int	handle_heredoc(char *delimiter)
{
	int		pipe_fd[2];
	char	*line;
	size_t	len;

	line = NULL;
	handle_pipe_failure(pipe(pipe_fd), "pipe");
	while (TRUE)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (handle_eoheredoc(pipe_fd));
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, len);
		write(pipe_fd[1], "\n", 1); // Restaurer le newline
		free(line);
	}
	close(pipe_fd[1]);
	handle_dup_failure(dup2(pipe_fd[0], STDIN_FILENO), "dup2");
	close(pipe_fd[0]);
	return (0);
}
*/

static void	close_pipe_ends(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

static void	write_line_to_pipe(int pipe_fd[2], char **line_addr)
{
	size_t	len;
	char *line;

	line = *line_addr;
	len = ft_strlen(line);
	write(pipe_fd[1], line, len);
	write(pipe_fd[1], "\n", 1); // Restaurer le newline
	free(line);
	line = NULL;
}

static int	check_delimiter(char **line_addr, char *delimiter)
{
	char	*line;

	line = *line_addr;
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		*line_addr = NULL;
		return (1);
	}
	return (0);
}

static int	read_and_write_heredoc(int pipe_fd[2], char *delimiter)
{
	char	*line;
	size_t	len;

	while (TRUE)
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (1);
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (check_delimiter(&line, delimiter))
			break ;
		write_line_to_pipe(pipe_fd, &line);
	}
	if (line)
		free(line);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int	pipe_fd[2];

	handle_pipe_failure(pipe(pipe_fd), "pipe");
	if (read_and_write_heredoc(pipe_fd, delimiter))
	{
		close_pipe_ends(pipe_fd);
		return (handle_eoheredoc(pipe_fd));
	}
	close(pipe_fd[1]);
	handle_dup_failure(dup2(pipe_fd[0], STDIN_FILENO), "dup2");
	close(pipe_fd[0]);
	return (0);
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

/*
void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

static char	*ft_append_heredoc(char *input, char *line, size_t *total_length)
{
	char	*new_input;

	new_input = ft_realloc(input, *total_length + ft_strlen(line) + 1);
	if (!new_input)
	{
		free(input);
		free(line);
		perror("Memory allocation failed");
		return (NULL);
	}
	ft_strlcpy(new_input + *total_length, line, INT_MAX);
	*total_length += ft_strlen(line);
	return (new_input);
}

static int	is_delimiter(char *line, char *delimiter)
{
	if (!line)
		return (1);
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	return (0);
}


char	*read_heredoc(char *delimiter)
{
	char	*input;
	char	*line;
	size_t	total_length;

	input = NULL;
	total_length = 0;
	while (1)
	{
		line = readline("> ");
		if (is_delimiter(line, delimiter))
			break ;
		input = ft_append_heredoc(input, line, &total_length);
		free(line);
		if (!input)
			return (NULL);
	}
	return (input);
}
*/