/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 12:08:18 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t	ft_strnlen(char *s, size_t max)
{
	size_t	i;

	i = 0;
	while (s[i] && i < max)
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstr_len;
	size_t	len_cpy;

	dstr_len = 0;
	if (dst)
		dstr_len = ft_strnlen(dst, dstsize);
	if (dstr_len == dstsize)
		return (dstr_len + ft_strlen(src));
	len_cpy = ft_strlcpy(dst + dstr_len, (char *)src, dstsize - dstr_len);
	return (dstr_len + len_cpy);
}
