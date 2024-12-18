/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/18 14:16:39 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	split_node(t_list *gc, t_btree *root, char *sep)
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
		content = gc_malloc(&gc, 1, sizeof(t_btree_content));
		if (!content)
			minishell_exit(gc);
		content->cmd = substr_left(str, found);
		root->left = btree_create_node(content);
		content = gc_malloc(&gc, 1, sizeof(t_btree_content));
		if (!content)
			minishell_exit(gc);
		content->cmd = substr_right(str, found);
		root->right = btree_create_node(content);
		content = gc_malloc(&gc, 1, sizeof(t_btree_content));
		if (!content)
			minishell_exit(gc);
		content->cmd = found;
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
		content = NULL;
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