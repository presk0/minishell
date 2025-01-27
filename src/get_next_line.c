/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 19:51:40 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*pop_line(char *buff)
{
	char	*line;
	char	*carriage_return;

	line = NULL;
	carriage_return = ft_strchr(buff, '\n');
	if (!carriage_return)
	{
		line = ft_substr(buff, 0, ft_strlen(buff) + 1);
		*buff = '\0';
	}
	else
	{
		line = ft_substr(buff, 0, carriage_return - buff + 1);
		ft_strlcpy(buff, carriage_return + 1, BUFFER_SIZE);
	}
	return (line);
}

char	*clean_lines(char **next_line, char **buff)
{
	if (next_line)
	{
		free(*next_line);
		*next_line = NULL;
	}
	if (buff)
	{
		free(*buff);
		*buff = NULL;
	}
	return (NULL);
}

char	*load_until_line(int fd, char **buff)
{
	int		read_val;
	char	*next_line;
	char	*tmp;
	char	*line_buff;

	read_val = 1;
	next_line = pop_line(*buff);
	while (!ft_strchr(next_line, '\n') && read_val > 0)
	{
		read_val = read(fd, *buff, BUFFER_SIZE);
		if (read_val >= 0)
		{
			(*buff)[read_val] = 0;
			line_buff = pop_line(*buff);
			tmp = ft_strjoin(next_line, line_buff);
			clean_lines(&next_line, &line_buff);
			next_line = tmp;
		}
		else
			return (clean_lines(&next_line, NULL));
	}
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*next_line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	if (!buff)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		buff[0] = '\0';
	}
	next_line = NULL;
	if (ft_strchr(buff, '\n'))
		next_line = pop_line(buff);
	else
		next_line = load_until_line(fd, &buff);
	if (!next_line || (next_line && !*next_line))
		clean_lines(&next_line, &buff);
	return (next_line);
}
