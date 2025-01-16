/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_export_utils.c                                :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/23 16:31:47 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 12:14:36 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	sort_export(t_list *gc, t_export **first)
{
	t_export	*node;
	int			i;

	node = (*first);
	i = 0;
	while (node != NULL)
	{
		i++;
		node = node->next;
	}
	while (i--)
	{
		node = (*first);
		if (ft_strcmp((*first)->next->line, (*first)->line) < 0)
			swap_first(gc, first);
		node = (*first);
		while (node->next->next != NULL)
		{
			if (ft_strcmp(node->next->next->line, node->next->line) < 0)
				swap_next(gc, node);
			node = node->next;
		}
	}
}

void	swap_first(t_list *gc, t_export **first)
{
	t_export	*second;

	(void)gc;
	second = (*first)->next;
	(*first)->next = second->next;
	second->next = (*first);
	(*first) = second;
	second = (*first)->next;
}

void	swap_next(t_list *gc, t_export *first)
{
	t_export	*second;

	(void)gc;
	second = first->next;
	first->next = second->next;
	second->next = first->next->next;
	first->next->next = second;
}
