/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 12:18:26 by supersko          #+#    #+#             */
/*   Updated: 2024/12/18 14:27:12 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst && del)
	{
		if (lst->content)
			del(lst->content);
		lst->content = NULL;
		lst->next = NULL;
		free(lst);
		//lst = NULL;
	}
	if (!del)
		ft_errmsg("[ft_lstdelone] missing del function?\n");
}
