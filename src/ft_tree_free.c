/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 19:54:16 by nidionis         ###   ########.fr       */
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
		gc_free_item(&g_d.gc, node_content->cmd);
	free_token(node_content->token);
	gc_free_item(&g_d.gc, node_content);
}

void	gc_free_tree(t_list *gc, t_btree **r, void (*f_free)(t_list *gc,
			void *content))
{
	t_btree	*node;

	(void)gc;
	if (!r || !*r)
		return ;
	node = *r;
	gc_free_tree(g_d.gc, &node->left, f_free);
	gc_free_tree(g_d.gc, &node->right, f_free);
	if (f_free)
		f_free(g_d.gc, node->content);
	gc_free_item(&g_d.gc, node);
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
