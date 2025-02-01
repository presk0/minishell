/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	malloc_len(char const *s, unsigned int start, size_t len)
{
	size_t	ret;
	size_t	slen;

	slen = ft_strlen(s);
	if (slen < start)
		return (0);
	ret = slen - start;
	if (len < ret)
		ret = len;
	return (ret);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*return_val;

	if (!s)
		return (NULL);
	len = malloc_len(s, start, len);
	substr = (char *)ft_calloc(len + 1, sizeof(char));
	if (!substr)
		return (NULL);
	while (start--)
	{
		if (!*s++)
		{
			substr[0] = '\0';
			return (substr);
		}
	}
	return_val = substr;
	while (len-- && *s)
		*substr++ = *s++;
	return (return_val);
}

/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	printf("%s\n", ft_substr(argv[1], atoi(argv[2]), atoi(argv[3])));
}
*/
