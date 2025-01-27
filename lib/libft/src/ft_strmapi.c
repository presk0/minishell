/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:16:24 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	les parametres de f sont imposes arbitrairement : i et s[i] */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*ret;

	if (s && f)
	{
		len = ft_strlen(s);
		ret = (char *)malloc((len + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		ret[len] = '\0';
		while (len--)
			ret[len] = f(len, s[len]);
		return (ret);
	}
	return (NULL);
}
