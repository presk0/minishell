/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2024/12/15 21:48:39 by nidionis         ###   ########.fr       */
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

/*
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
*/

/*************  ✨ Codeium Command ⭐  *************/
/**
 * Prints the binary tree in a visually appealing way.
 *
 * The function takes a binary tree rooted at `root`, and a callback function
 * `print` that will be called on each node's content. The `space` parameter
 * is used to keep track of the indentation level.
 *
 * The tree is printed inorder, meaning that the left subtree is printed first,
 * then the root node, and finally the right subtree. The root node is printed
 * with an indentation level equal to `space`, and the left and right subtrees
 * are printed with an indentation level of `space + 3`.
 *
 * If the node's content is NULL, nothing is printed for that node.
 */
/******  fb5c55b6-aae8-4819-9286-1c2369e3f9c1  *******/
void print_tree(t_btree *root, int space, void (*print)(void *content)) {
    if (root == NULL) {
        return;
    }
    print_tree(root->right, space + 3, print);
    for (int i = 0; i < space; i++) {
        printf(" ");
    }
    if (root->content)
        print(root->content);
    printf("\n");
    print_tree(root->left, space + 3, print);
}

void display_tree(t_btree *root, void(*print)(void *content))
{
    print_tree(root, 0, print);
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

/*
void	print_node_content(void *content)
{
	printf("%s\n", (char *)content);
}


void	*split_function(t_btree *node int is_right)
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
