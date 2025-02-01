/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
