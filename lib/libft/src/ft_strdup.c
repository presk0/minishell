/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:15:47 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	size_t	s_len;
	char	*scpy;

	s_len = ft_strlen(str);
	if (s_len > n)
		s_len = n;
	scpy = (char *)malloc((s_len + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	scpy[s_len] = '\0';
	i = -1;
	while (++i < s_len)
		scpy[i] = str[i];
	return (scpy);
}

char	*ft_strdup(const char *str)
{
	size_t	i;
	size_t	s_len;
	char	*scpy;

	s_len = ft_strlen(str);
	scpy = (char *)malloc((s_len + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	scpy[s_len] = '\0';
	i = -1;
	while (++i < s_len)
		scpy[i] = str[i];
	return (scpy);
}
