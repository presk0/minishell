/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:13:27 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
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
