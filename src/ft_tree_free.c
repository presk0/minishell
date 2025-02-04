/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 01:06:57 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	gc_free_node_content(t_list *gc, void *content)
{
	t_btree_content	*node_content;

	(void)gc;
	node_content = (t_btree_content *)content;
	if (!node_content)
		return ;
	if (node_content->cmd)
		gc_free_item(&gc, node_content->cmd);
	free_token(&gc, node_content->token);
	gc_free_item(&gc, node_content);
}

void	gc_free_tree(t_list *gc, t_btree **r, void (*f_free)(t_list *gc,
			void *content))
{
	t_btree	*node;

	(void)gc;
	if (!r || !*r)
		return ;
	node = *r;
	gc_free_tree(gc, &node->left, f_free);
	gc_free_tree(gc, &node->right, f_free);
	if (f_free)
		f_free(gc, node->content);
	gc_free_item(&gc, node);
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
