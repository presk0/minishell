/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *str, const char *ndl, size_t len)
{
	char	*p_str;
	size_t	ndl_len;

	p_str = (char *)str;
	ndl_len = ft_strlen(ndl);
	if (len >= ndl_len)
		while (*p_str && len-- && len + 1 >= ndl_len)
			if (!ft_strncmp(p_str++, ndl, ndl_len))
				return (--p_str);
	if (!*ndl)
		return (p_str);
	return (NULL);
}

/*
#include <bsd/string.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	*s1;
	char	*s2;
	int		n;

	(void)argc;
	(void)argv;
	s1 = 0;
	//char	*s1 = argv[1];
	//char	*s2 = argv[2];
	//char	*s1 = "hello";
	s2 = "fake";
	n = atoi(argv[3]);
	(void)s1;
	(void)s2;
	(void)n;
	printf("ft_funct: %s\n", ft_strnstr(s1, s2, n));
	printf("original: %s\n", strnstr(s1, s2, n));
}
*/
