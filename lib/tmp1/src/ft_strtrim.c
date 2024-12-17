/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 14:33:46 by supersko          #+#    #+#             */
/*   Updated: 2024/10/30 21:13:00 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	char	*ret;
	char	*new_str;
	int		end;

	if (!str)
		return (NULL);
	while (*str && ft_strchr(set, *str))
		str++;
	end = ft_strlen(str);
	while (end >= 0 && ft_strchr(set, str[end]))
		end--;
	new_str = ft_calloc(++end + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ret = new_str;
	while (end-- && *str)
		*new_str++ = *str++;
	return (ret);
}

/*
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	printf("%s\n", ft_strtrim(argv[1], argv[2]));
}
*/
