/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/02 20:00:18 by nidionis         ###   ########.fr       */
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


void gc_free_node_content(t_list **gc, void *content)
{
    t_btree_content *node_content = (t_btree_content *)content;

    if (!node_content)
        return;
    if (node_content->cmd)
        gc_free_item(gc, node_content->cmd);
    gc_free_item(gc, node_content);
}

void gc_free_tree(t_list **gc, t_btree **r, void (*f_free)(t_list **gc, void *content))
{
    if (!r || !*r)
        return;
    t_btree *node = *r;
    gc_free_tree(gc, &node->left, f_free);
    gc_free_tree(gc, &node->right, f_free);
    if (f_free)
        f_free(gc, node->content);
    gc_free_item(gc, node);
    *r = NULL;
}

void	print_node_content(void *content)
{
	t_btree_content	*stuff;

	stuff = content;
	if (stuff)
		printf("%s", stuff->token.cmd);
	else
		printf("%s", stuff->cmd);
}