/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 22:17:26 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*shift_char(char *str, size_t shift_len)
{
	size_t	i;

	if (ft_strlen(str) < shift_len)
		return (NULL);
	i = shift_len;
	if (str)
	{
		while (str[i])
		{
			str[i - shift_len] = str[i];
			i++;
		}
	}
	return (str);
}

char	*shift_left(char *str, size_t shift_len)
{
	char	*ret;

	ret = str;
	if (str)
		while (*str)
			str = shift_char(str, shift_len);
	return (ret);
}

