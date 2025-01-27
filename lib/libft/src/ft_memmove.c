/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:14:52 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memrcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*g_d;
	unsigned char	*s;

	g_d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (len--)
		g_d[len] = s[len];
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
	{
		ft_errmsg("[ft_memmove] sdt or src is NULL\n");
		return (NULL);
	}
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
		ft_memrcpy(dst, src, len);
	return (dst);
}
