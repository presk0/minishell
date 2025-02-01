/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:36:39 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 17:13:48 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*buff;

	if (new && lst)
	{
		buff = ft_lstlast(*lst);
		if (!buff)
			*lst = new;
		else
			buff->next = new;
	}
	else
		ft_errmsg("[ft_lstadd_back] stop coding with your feet ?\n");
}
