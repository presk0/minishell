/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2024/12/11 20:41:10 by nidionis         ###   ########.fr       */
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
	t_btree *root, void (*applyf)(void *, t_btree **node))
{
	if (!root)
		return ;
	applyf(root->content, &root);
	btree_apply_prefix(root->left, applyf);
	btree_apply_prefix(root->right, applyf);
}

void	btree_apply_infix(\
	t_btree *root, void (*applyf)(void *, t_btree **node))
{
	if (!root)
		return ;
	btree_apply_infix(root->left, applyf);
	applyf(root->content, &root);
	btree_apply_infix(root->right, applyf);
}

void	btree_apply_postfix(\
	t_btree *root, void (*applyf)(void *, t_btree **node))
{
	if (!root)
		return ;
	btree_apply_postfix(root->left, applyf);
	btree_apply_postfix(root->right, applyf);
	applyf(root->content, &root);
}

t_btree	*btree_split_node(t_btree *node, void *(*splitf)(void *, int))
{
	t_btree	*node_left;
	t_btree	*node_right;

	if (!node || !splitf)
		return (NULL);
	node_left = splitf(node->content, LEFT);
	node_right = splitf(node->content, RIGHT);
	node->left = btree_create_node(node_left);
	node->right = btree_create_node(node_right);
	splitf(node->content, ROOT);
	return (node);
}

void	print_node_content(void *content)
{
	printf("%s\n", (char *)content);
}

void	print_tree_pretty(t_btree *root)
{
	if (!root)
		return ;
	print_tree_pretty(root->left);
	print_node_content(root->content);
	print_tree_pretty(root->right);
}

void print_tree(t_btree *root, int space) {
    if (root == NULL) {
        return;
    }
    space += 10;
    print_tree(root->right, space);
    printf("\n");
    for (int i = 10; i < space; i++) {
        printf(" ");
    }
    printf("%s\n", (char *)root->content);
    print_tree(root->left, space);
}

void display_tree(t_btree *root)
{
    print_tree(root, 0);
}

void	free_tree(t_btree *root)
{
	if (!root)
		return ;
	free_tree(root->left);
	free_tree(root->right);
	free(root);
}

/*
void	print_node_content(void *content)
{
	printf("%s\n", (char *)content);
}


void	*split_function(void *content, int is_right)
{
	char *original = (char *)content;
	char *new_content = (char *)malloc(100);
	if (!new_content)
	return NULL;
	if (is_right)
	snprintf(new_content, 100, "%s.Right", original);
	else
	snprintf(new_content, 100, "%s.Left", original);

	return new_content;
}

int	main()
{
	t_btree *root = btree_create_node("Root");
	root->left = btree_create_node("Left");
	root->right = btree_create_node("Right");
	printf("Splitting root node:\n");
	btree_split_node(root, split_function);
	printf("In-order traversal:\n");
	btree_apply_inorder(root, print_node_content);
	return 0;
}
*/
