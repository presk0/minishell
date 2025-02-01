/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = dst;
	s = (void *)src;
	if (dst == src)
		return (dst);
	if (!dst || !src)
	{
		ft_errmsg("[ft_memcmp] (!dst || !src)\n");
		return (NULL);
	}
	while (len--)
		*d++ = *s++;
	return (dst);
}
