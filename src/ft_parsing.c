/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/31 16:28:12 by nidionis         ###   ########.fr       */
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
			minishell_exit(gc);
		}
	}
	return (ret);
}

char	*substr_right(t_list *gc, char *node_content, char *found)
{
	char	*ret;

	(void)node_content;
	while (found[0] == found[1])
		found++;
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
			minishell_exit(gc);
		}
	}
	return (ret);
}

int	is_quoted(char c, int reset)
{
	static int	quote;

	if (reset)
		quote = 0;
	if (c == '\'')
	{
		if (quote == 1 || !quote)
			quote = !quote;
	}
	if (c == '"')
	{
		if (quote == 2)
			quote = 0;
		if (quote == 0)
			quote = 2;
	}
	return (quote);
}

char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len)
{
	char		*p_str;
	size_t		ndl_len;

	if (!str || !ndl)
		return (NULL);
	p_str = (char *)str;
	ndl_len = ft_strlen(ndl);
	is_quoted(0, 1);
	if (len >= ndl_len)
	{
		while (*p_str && len-- && len + 1 >= ndl_len)
		{
			if (!is_quoted(*p_str, 0) && !ft_strncmp(p_str, ndl, ndl_len))
				return (p_str);
			p_str++;
		}
	}
	if (!*ndl)
		return (p_str);
	return (NULL);
}
