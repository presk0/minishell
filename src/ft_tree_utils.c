/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/02 16:09:40 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_btree_content	*new_content(t_list *gc)
{
	t_btree_content	*content;
	void			*gc_ok;

	content = malloc(sizeof(t_btree_content));
	gc_ok = gc_append(&gc, content);
	if (!gc_ok || !content)
		minishell_exit(gc);
	return (content);
}

t_btree	*new_node(t_list *gc, t_btree_content *content)
{
	t_btree	*node;
	void	*gc_ok;

	node = NULL;
	if (content)
	{
		node = btree_create_node(content);
		gc_ok = gc_append(&gc, node);
		if (!gc_ok || !node)
			minishell_exit(gc);
	}
	return (node);
}

void	split_node(t_list *gc, t_btree *root, char *sep)
{
	char			*str;
	char			*sep_found;
	t_btree_content	*content;

	if (root->left || root->right)
		return ;
	content = root->content;
	str = content->cmd;
	sep_found = ft_strnstr_quotes(str, sep, ft_strlen(str));
	if (sep_found)
	{
		content = new_content(gc);
		content->cmd = substr_left(gc, str, sep_found);
		if (content->cmd)
			root->left = new_node(gc, content);
		content = new_content(gc);
		content->cmd = substr_right(gc, str, sep_found);
		if (content->cmd)
			root->right = new_node(gc, content);
		content = root->content;
		content->cmd = sep_found;
		content->token = sep;
		root->content = content;
	}
}

void	btree_split(t_list *gc, t_btree *root, char *sep)
{
	if (!root)
		return ;
	split_node(gc, root, sep);
	if (root->left)
		btree_split(gc, root->left, sep);
	if (root->right)
		btree_split(gc, root->right, sep);
}

void	free_node_content(void *stuff)
{
	t_btree_content	*content;

	content = stuff;
	if (content)
	{
		if (content->cmd)
		{
			free(content->cmd);
			content->cmd = NULL;
		}
		if (content->token)
		{
			free(content->token);
			content->token = NULL;
		}
		free(content);
	}
}

void	print_node_content(void *content)
{
	t_btree_content	*stuff;

	stuff = content;
	if (stuff->token)
		printf("%s", stuff->token);
	else
		printf("%s", stuff->cmd);
}
