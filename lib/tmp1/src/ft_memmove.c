/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2024/12/11 13:46:06 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_memrcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (len--)
		d[len] = s[len];
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
