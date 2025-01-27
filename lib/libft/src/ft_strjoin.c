/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:15:57 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*ret;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = malloc(len_s2 + len_s1 + 1 * sizeof(char));
	if (!ret)
		return (NULL);
	*ret = '\0';
	if (s1)
		ft_strlcpy(ret, s1, ++len_s1);
	if (s2)
		ft_strlcat(ret, s2, len_s1 + len_s2);
	return (ret);
}

char	*ft_strjoin_free1(char *s1, char *s2)
{
	char	*str;
	size_t	str_size;

	if (!s1 || !s2)
		return (NULL);
	str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(str_size * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, str_size);
	free(s1);
	return (str);
}

char	*ft_strjoin_free2(char *s1, char *s2)
{
	char	*str;
	size_t	str_size;

	if (!s1 || !s2)
		return (NULL);
	str_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(str_size * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, str_size);
	free(s2);
	return (str);
}

/* peut remplacer ft_strlc..
	i = -1;
	if (s1)
		while (++i < len_s1)
			ret[i] = s1[i];
	i = -1;
	if (s2)
		while (s2[++i])
			ret[i + len_s1] = s2[i];
*/
