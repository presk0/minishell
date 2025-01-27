/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:15:03 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	loop_norminette(char **str_addr, va_list ap, int *p_itm, int *ret_val)
{
	if (**str_addr == '%')
	{
		*p_itm = print_item(ap, *(++(*str_addr)));
		if (*p_itm == -1)
			*ret_val = -1;
		if (*ret_val != -1)
			*ret_val += *p_itm;
	}
	else
	{
		write(FD, *str_addr, 1);
		if (*ret_val != -1)
			(*ret_val)++;
	}
	if (**str_addr)
		(*str_addr)++;
}
