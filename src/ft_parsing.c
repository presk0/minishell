/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <nidionis@student.42.fr>			+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 00:10:03 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char *str)
{
	while (*str)
	{
		if (!ft_strchr(WHITE_SPACE, *str))
			return (0);
		str++;
	}
	return (1);
}

char	*substr_left(t_data *d, char *node_content, char *found)
{
	char	*ret;

	ret = ft_substr(node_content, 0, found - node_content);
	if (ret && is_blank(ret))
	{
		free(ret);
		ret = NULL;
	}
	if (ret)
	{
		if (!gc_append(&d->gc, ret))
		{
			minishell_exit(d, "substr_left", -1);
		}
	}
	return (ret);
}

char	*substr_right(t_data *d, char *node_content, char *found)
{
	char	*ret;

	(void)node_content;
	found++;
	ret = ft_substr(found, 0, ft_strlen(found));
	if (ret && is_blank(ret))
	{
		free(ret);
		ret = NULL;
	}
	if (ret)
	{
		if (!gc_append(&d->gc, ret))
		{
			minishell_exit(d, "substr_right", -1);
		}
	}
	return (ret);
}

void	split_node(t_data *d, t_btree *root, char *sep)
{
	char			*cmd;
	char			*sep_found;
	t_btree_content	*content;

	if (root->left || root->right)
		return ;
	cmd = ((t_btree_content *)root->content)->cmd;
	sep_found = ft_strnstr_quotes(cmd, sep, ft_strlen(cmd));
	if (sep_found)
	{
		content = gc_malloc_btree_content(d);
		content->cmd = substr_left(d, cmd, sep_found);
		if (content->cmd)
			root->left = new_node(d, content);
		content = gc_malloc_btree_content(d);
		content->cmd = substr_right(d, cmd, sep_found);
		if (content->cmd)
			root->right = new_node(d, content);
		content = root->content;
		gc_free_item(&d->gc, content->cmd);
		content->cmd = gc_strdup(&d->gc, sep);
	}
}

void	btree_split(t_data *d, t_btree *root, char *sep)
{
	if (!root)
		return ;
	split_node(d, root, sep);
	if (root->left)
		btree_split(d, root->left, sep);
	if (root->right)
		btree_split(d, root->right, sep);
}
