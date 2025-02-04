/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_tree_utils.c                                    :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 01:06:42 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

t_btree_content	*gc_malloc_btree_content(t_data *d)
{
	t_btree_content	*content;
	void			*gc_ok;

	content = ft_calloc(sizeof(t_btree_content), 1);
	gc_ok = gc_append(&d->gc, content);
	if (!gc_ok || !content)
		minishell_exit(d, "[gc_malloc_btree_content]", -1);
	return (content);
}

t_btree	*new_node(t_data *d, t_btree_content *content)
{
	t_btree	*node;
	void	*gc_ok;

	node = NULL;
	if (content)
	{
		node = btree_create_node(content);
		gc_ok = gc_append(&d->gc, node);
		if (!gc_ok || !node)
			minishell_exit(d, "new_node", -1);
	}
	return (node);
}

void	free_token(t_list **gc, t_token token)
{
	if (token.cmd)
		gc_free_item(gc, token.cmd);
	if (token.args)
		while (*token.args)
			gc_free_item(gc, *token.args++);
	if (token.redir_in)
		gc_free_item(gc, token.redir_in);
	if (token.redir_out)
		gc_free_item(gc, token.redir_out);
}
