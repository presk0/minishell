/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:13:46 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list **lst_addr, void (*del)(void *))
{
	t_list	*lst;

	lst = *lst_addr;
	if (lst)
		lst = *lst_addr;
	if (lst && del)
	{
		if (lst->content)
			del(lst->content);
		lst->content = NULL;
		lst->next = NULL;
		free(lst);
		lst = NULL;
	}
	if (!del)
		ft_errmsg("[ft_lstdelone] missing del function?\n");
}
