/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:53:31 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/01 17:18:31 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = ft_calloc(n + 1, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, n + 1);
	return (str);
}
