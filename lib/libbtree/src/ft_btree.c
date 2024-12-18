/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2024/12/18 13:22:28 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "btree.h"

t_btree	*btree_create_node(void *content)
{
	t_btree	*new_node;

	new_node = (t_btree *)malloc(sizeof(t_btree));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

void	btree_apply_prefix(\
	t_btree *root, void *(*applyf)(t_btree *node))
{
	if (!root)
		return ;
	applyf(root);
	if (root->left)
		btree_apply_prefix(root->left, applyf);
	if (root->right)
		btree_apply_prefix(root->right, applyf);
}

void	btree_apply_infix(\
	t_btree *root, void *(*applyf)(t_btree *node))
{
	if (!root)
		return ;
	if (root->left)
		btree_apply_infix(root->left, applyf);
	applyf(root);
	if (root->right)
		btree_apply_infix(root->right, applyf);
}

void	btree_apply_postfix(\
	t_btree *root, void *(*applyf)(t_btree *node))
{
	if (!root)
		return ;
	if (root->right)
		btree_apply_postfix(root->left, applyf);
	if (root->left)
		btree_apply_postfix(root->right, applyf);
	applyf(root);
}

void	free_tree(t_btree *root, void (*f_free)(void *content))
{
	if (!root)
		return ;
	if (root->left)
		free_tree(root->left, f_free);
	if (root->right)
		free_tree(root->right, f_free);
	if (root->content)
		f_free(root->content);
	root->content = NULL;
	free(root);
	root = NULL;
}
