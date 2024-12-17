/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2024/11/16 15:17:02 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*mem;
	char	byte;

	mem = (char *)s;
	byte = c;
	if (!s)
	{
		ft_errmsg("[ft_memchr] !s\n");
		return (NULL);
	}
	if (n)
	{
		while (n--)
		{
			if (*mem == byte)
				return (mem);
			mem++;
		}
	}
	return (NULL);
}
