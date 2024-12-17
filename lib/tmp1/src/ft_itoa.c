/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:17:07 by supersko          #+#    #+#             */
/*   Updated: 2024/11/16 15:16:38 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(long int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	make_str(long int *n, char *str, int len)
{
	if (*n < 0)
	{
		*str++ = '-';
		len--;
		*n *= -1;
	}
	while (len--)
	{
		str[len] = *n % 10 + '0';
		*n /= 10;
	}
}

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long int	num;

	num = n;
	len = ft_intlen(num);
	str = malloc(len + 1 * sizeof(char));
	if (!str)
	{
		ft_errmsg("[ft_itoa] cannot malloc");
		return (NULL);
	}
	str[len] = '\0';
	make_str(&num, str, len);
	return (str);
}
