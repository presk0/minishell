/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 16:48:16 by supersko          #+#    #+#             */
/*   Updated: 2025/02/01 05:47:15 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_atoi(const char *str0)
{
	int			sign;
	long int	nbr;
	char		*str;

	sign = 1;
	str = (char *)str0;
	nbr = 0;
	if (str0)
	{
		while (*str == ' ' || (*str >= 9 && *str <= 13))
			str++;
		if (*str == '-' || *str == '+')
			if (*str++ == '-')
				sign *= -1;
		while (ft_isdigit(*str))
			nbr = *str++ - '0' + nbr * 10;
	}
	return (sign * nbr);
}
