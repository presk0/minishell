/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2024/11/16 15:23:31 by nidionis         ###   ########.fr       */
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
		ret = (char *) malloc((len + 1) * sizeof(char));
		if (!ret)
			return (NULL);
		ret[len] = '\0';
		while (len--)
			ret[len] = f(len, s[len]);
		return (ret);
	}
	return (NULL);
}
