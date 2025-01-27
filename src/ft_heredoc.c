/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:31:58 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_pipe_ends(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	write_line_to_pipe(int pipe_fd[2], char **line_addr)
{
	size_t	len;
	char	*line;

	line = *line_addr;
	len = ft_strlen(line);
	write(pipe_fd[1], line, len);
	write(pipe_fd[1], "\n", 1);
	free(line);
	line = NULL;
}

int	check_delimiter(char **line_addr, char *delimiter)
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

int	read_and_write_heredoc(int pipe_fd[2], char *delimiter)
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
