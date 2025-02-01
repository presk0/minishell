/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n)
	{
		while (--n && *s1 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		return ((unsigned char)*s1 - (unsigned char)*s2);
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	printf("my_func: %i\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
	printf("original: %i\n", strncmp(argv[1], argv[2], atoi(argv[3])));
}
*/
