/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_quotes_utils.c                                  :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/22 11:35:16 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	strlen_wd_quoted(char *cmd)
{
	int	len;

	is_quoted(0, BUFF_STRLEN, RESET);
	len = 0;
	while (*cmd)
	{
		if (!is_quoted(*cmd, BUFF_STRLEN, SAVE))
			if (is_operand(cmd) || ft_strchr(WHITE_SPACE, *cmd))
				break ;
		cmd++;
		len++;
	}
	return (len);
}

char	*strdup_wd_quote(char *cmd)
{
	int		wd_len_quoted;
	char	*duplicated;
	char	*out;

	wd_len_quoted = strlen_wd_quoted(cmd);
	duplicated = gc_malloc(&d.gc, 1, wd_len_quoted + 1);
	if (!duplicated)
		return (NULL);
	out = duplicated;
	while (wd_len_quoted--)
		*duplicated++ = *cmd++;
	*duplicated = '\0';
	return (out);
}

int	is_quoted(char c, int buff, int action)
{
	static int	quote[BUFF_QUOTE_MAX];

	if (action == READ)
		return (quote[buff]);
	if (action == RESET)
		quote[buff] = 0;
	if (c == '\'')
	{
		if (quote[buff] == 1 || !quote[buff])
			quote[buff] = !quote[buff];
	}
	if (c == '"')
	{
		if (quote[buff] == 2)
			quote[buff] = 0;
		else if (quote[buff] == 0)
			quote[buff] = 2;
	}
	return (quote[buff]);
}

char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len)
{
	char	*p_str;
	size_t	ndl_len;

	if (!str || !ndl)
		return (NULL);
	p_str = (char *)str;
	ndl_len = ft_strlen(ndl);
	is_quoted(0, BUFF_STRNSTR, RESET);
	if (len >= ndl_len)
	{
		while (*p_str && len-- && len + 1 >= ndl_len)
		{
			if (!is_quoted(*p_str, BUFF_STRNSTR, SAVE) && !ft_strncmp(p_str,
					ndl, ndl_len))
				return (p_str);
			p_str++;
		}
	}
	if (!*ndl)
		return (p_str);
	return (NULL);
}
