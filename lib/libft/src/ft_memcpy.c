/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:14:46 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char	*g_d;
	char	*s;

	g_d = dst;
	s = (void *)src;
	if (dst == src)
		return (dst);
	if (!dst || !src)
	{
		ft_errmsg("[ft_memcmp] (!dst || !src)\n");
		return (NULL);
	}
	while (len--)
		*g_d++ = *s++;
	return (dst);
}
