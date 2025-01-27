/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:14:28 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
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
