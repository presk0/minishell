/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 00:34:14 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

char	*del_char(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i++])
			str[i - 1] = str[i];
	}
	return (str);
}

char	*rm_quotes(char *str)
{
	char	*ret;
	int		last_state;

	ret = str;
	last_state = 0;
	is_quoted(0, BUFF_RMQUOTES, RESET);
	if (str)
	{
		while (*str)
		{
			if (last_state != is_quoted(*str, BUFF_RMQUOTES, SAVE))
			{
				last_state = is_quoted(*str, BUFF_RMQUOTES, READ);
				str = del_char(str);
			}
			else
				str++;
		}
	}
	return (ret);
}

int	strlen_char_simple_quoted(char *cmd, char c, int buff)
{
	int	len;

	len = 0;
	if (!cmd)
		return (0);
	while (*cmd)
	{
		if (is_quoted(*cmd, buff, SAVE) != SIMPLE_QUOTE)
			if (*cmd == c)
				break ;
		cmd++;
		len++;
	}
	return (len);
}
