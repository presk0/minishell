/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 15:55:04 by supersko          #+#    #+#             */
/*   Updated: 2024/11/16 15:21:08 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t		i;
	size_t		s_len;
	char		*scpy;

	s_len = ft_strlen(str);
	scpy = (char *) malloc((s_len + 1) * sizeof(char));
	if (!scpy)
		return (NULL);
	scpy[s_len] = '\0';
	i = -1;
	while (++i < s_len)
		scpy[i] = str[i];
	return (scpy);
}
