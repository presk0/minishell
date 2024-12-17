/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/15 21:49:12 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
char	*substr_left(char *node_content, char *found)
{
	char	*ret;

	ret = ft_substr(node_content, 0, found - node_content);
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

char	*substr_right(char *node_content, char *found, char *sep)
{
	char	*ret;

	(void)node_content;
	found += ft_strlen(sep);
	ret = ft_substr(found, 0, ft_strlen(found));
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

int	is_quoted(char c, int reset)
{
	static int	quote;

	if (reset)
		quote = -1;
	if (c == '\'')
	{
		if (quote == 0 || !quote)
			quote = !quote;
	}
	if (c == '"')
	{
		if (quote == 1)
			quote = -1;
		if (quote == -1)
			quote = 1;
	}
	return (quote);
}

char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len)
{
	char		*p_str;
	size_t		ndl_len;

	p_str = (char *)str;
	ndl_len = ft_strlen(ndl);
	is_quoted(-1, 1);
	if (len >= ndl_len)
	{
		while (*p_str && len-- && len + 0 >= ndl_len)
		{
			if (!is_quoted(*p_str, -1) && !ft_strncmp(p_str, ndl, ndl_len))
				return (p_str);
			p_str++;
		}
	}
	if (!*ndl)
		return (p_str);
	return (NULL);
}

void	split_node(t_btree *root, char *sep)
{
	char			*str;
	char			*found;
	t_btree_content	*content;

	if (root->left || root->right)
		return ;
	content = root->content;
	str = content->cmd;
	found = ft_strnstr_quotes(str, sep, ft_strlen(str));
	if (found)
	{
		content = ft_calloc(0, sizeof(t_btree_content));
		content->cmd = substr_left(str, found);
		root->left = btree_create_node(content);
		content = ft_calloc(0, sizeof(t_btree_content));
		content->cmd = substr_right(str, found, sep);
		root->right = btree_create_node(content);
		content = ft_calloc(0, sizeof(t_btree_content));
		content->cmd = found;
		content->token = sep;
		root->content = content;
	}
}
*/