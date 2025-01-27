/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:14:11 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ret;
	t_list	*new;
	void	*cont;

	if (!lst)
		return (NULL);
	if (!del || !f)
		return (ft_errmsg("[ft_lstmap] f or del function is missing\n"), NULL);
	ret = NULL;
	while (lst)
	{
		cont = f(lst->content);
		new = ft_lstnew(cont);
		if (!new)
		{
			ft_errmsg("[ft_lstmap] ft_lstnew crashed\n");
			del(cont);
			return (ft_lstclear(&ret, del), NULL);
		}
		ft_lstadd_back(&ret, new);
		lst = lst->next;
	}
	return (ret);
}
