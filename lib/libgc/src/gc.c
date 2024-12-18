/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/18 13:31:41 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	clean_exit(t_list **gc_addr)
{
	t_list	*tmp;
	t_list	*gc;

	gc = *gc_addr;
	while (gc)
	{
		tmp = gc->next;
		ft_lstdelone(gc, free);
		gc = tmp;
	}
}

void	*gc_append(t_list **gc_addr, void *ptr)
{
	t_list	*new_garbage;

	new_garbage = ft_lstnew(ptr);
	if (!new_garbage)
		clean_exit(gc_addr);
	ft_lstadd_back(gc_addr, new_garbage);
	return (ptr);
}

void	*gc_malloc(t_list **gc_addr, size_t count, size_t size)
{
	void	*ptr;

	if (size)
		if (size * count / size != count)
			return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (NULL);
	gc_append(gc_addr, ptr);
	return (ptr);
}

void	gc_free_item(t_list **gc_addr, void *ptr)
{
	t_list	*gc;
	t_list	*prev;

	gc = *gc_addr;
	prev = NULL;
	while (gc)
	{
		if (gc->content == ptr)
		{
			if (prev)
				prev->next = gc->next;
			else
				*gc_addr = gc->next;
			ft_lstdelone(gc, free);
			break ;
		}
		prev = gc;
		gc = gc->next;
	}
}
