/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:36:39 by supersko          #+#    #+#             */
/*   Updated: 2024/10/31 13:49:01 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = malloc(sizeof(*new));
	if (!new)
	{
		ft_errmsg("[ft_lstnew] malloc crashed\n");
		return (NULL);
	}
	new->content = content;
	new->next = NULL;
	return (new);
}
