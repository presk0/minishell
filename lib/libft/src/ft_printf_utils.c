/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/12 13:17:17 by nidionis         ###   ########.fr       */
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
