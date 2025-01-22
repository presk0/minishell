/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/02/23 16:48:16 by supersko		  #+#	#+#			 */
/*   Updated: 2025/01/22 00:41:04 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

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

long int       ft_atoi_err(char *str)
{
       long int        sign;
       long int        nbr;

       sign = 1;
       while (ft_strchr("\t ", *str))
               str++;
       if (*str == '-' || *str == '+')
               if (*str++ == '-')
                       sign *= -1;
       nbr = 0;
       if (!ft_isdigit(*str))
               return (2147483649);
       while (ft_isdigit(*str))
       {
				nbr *= 10;
				nbr = *str++ - '0' + nbr * 10;
				if (nbr > 2147483648)
                       return (nbr);
       }
       if (*str)
               return (2147483649);
       nbr *= sign;
       return (nbr);
}
