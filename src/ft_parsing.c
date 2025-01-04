/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/04 17:34:11 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*substr_left(t_list *gc, char *node_content, char *found)
{
	char	*ret;

	ret = ft_substr(node_content, 0, found - node_content);
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	if (ret)
	{
		if (!gc_append(&gc, ret))
		{
			write(2, "[substr_left]\n", 14);
			minishell_exit(&gc);
		}
	}
	return (ret);
}

char	*substr_right(t_list *gc, char *node_content, char *found)
{
	char	*ret;

	(void)node_content;
	//while (found[0] == found[1])
	//	found++;
	found++;
	ret = ft_substr(found, 0, ft_strlen(found));
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	if (ret)
	{
		if (!gc_append(&gc, ret))
		{
			write(2, "[substr_right]\n", 14);
			minishell_exit(&gc);
		}
	}
	return (ret);
}

int	is_quoted(char c, int buff, int reset)
{
	static int	quote[BUFF_QUOTE_MAX];

	if (reset == RESET)
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
		if (quote[buff] == 0)
			quote[buff] = 2;
	}
	return (quote[buff]);
}

char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len)
{
	char		*p_str;
	size_t		ndl_len;

	if (!str || !ndl)
		return (NULL);
	p_str = (char *)str;
	ndl_len = ft_strlen(ndl);
	is_quoted(0, BUFF_STRNSTR, RESET);
	if (len >= ndl_len)
	{
		while (*p_str && len-- && len + 1 >= ndl_len)
		{
			if (!is_quoted(*p_str, BUFF_STRNSTR, SAVE) && !ft_strncmp(p_str, ndl, ndl_len))
				return (p_str);
			p_str++;
		}
	}
	if (!*ndl)
		return (p_str);
	return (NULL);
}
