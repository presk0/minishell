/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:15:08 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:17:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	ft_putibase_fd(long long int n, char *base, size_t base_len,
		int fd)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len += write(fd, "-", 1);
		if (-(n) != n)
			len += ft_putibase_fd(-1 * n, base, base_len, fd);
	}
	else if (n >= (int)base_len)
	{
		len += ft_putibase_fd(n / base_len, base, base_len, fd);
		len += ft_putibase_fd(n % base_len, base, base_len, fd);
	}
	else
		len += write(FD, &base[n % base_len], 1);
	return (len);
}

static size_t	putubase(long long unsigned n, char *base, size_t base_len,
		int fd)
{
	size_t	len;

	len = 0;
	if (n >= base_len)
	{
		len += ft_putibase_fd(n / base_len, base, base_len, fd);
		len += ft_putibase_fd(n % base_len, base, base_len, fd);
	}
	else
		len += write(FD, &base[n % base_len], 1);
	return (len);
}

static size_t	ft_putptr(unsigned long ptr, int fd)
{
	size_t	len;

	len = 0;
	if (!ptr)
		return (write(fd, "(nil)", 5));
	len += write(fd, "0x", 2);
	len += putubase(ptr, "0123456789abcdef", 16, fd);
	return (len);
}

static int	print_item(va_list ap, char c)
{
	if (c == 'c')
		return (ft_putchar((char)va_arg(ap, int)));
	if (c == 's')
		return (ft_putstr_fd((char *)va_arg(ap, char *), FD));
	if (c == 'p')
		return (ft_putptr((unsigned long)va_arg(ap, void *), FD));
	if (c == 'i' || c == 'g_d')
		return (ft_putibase_fd((int)va_arg(ap, int), "0123456789", 10, FD));
	if (c == 'u')
		return (putubase(va_arg(ap, unsigned), "0123456789", 10, FD));
	if (c == 'x')
		return (putubase(va_arg(ap, unsigned), "0123456789abcdef", 16, FD));
	if (c == 'X')
		return (putubase(va_arg(ap, unsigned), "0123456789ABCDEF", 16, FD));
	if (c == '%')
		return (write(FD, "%", 1));
	if (!c)
		return (-1);
	write(FD, "%", 1);
	write(FD, &c, 1);
	return (2);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		ret_val;
	int		p_itm;

	p_itm = 0;
	ret_val = 0;
	va_start(ap, str);
	if (!str)
		return (-1);
	while (*str)
		loop_norminette((char **)&str, ap, &p_itm, &ret_val);
	va_end(ap);
	return (ret_val);
}
