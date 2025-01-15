/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekrebs <ekrebs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:59:27 by nkieffer          #+#    #+#             */
/*   Updated: 2024/11/28 01:11:43 by ekrebs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_isdashn(char *str)
{
	size_t	i;

	if (str && str[0] != '-')
		return (0);
	if (str && str[1] != 'n')
		return (0);
	i = 1;
	while (str && str[i] != '\0' && str[i] == 'n')
		i++;
	if (str && str[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	int	is_n;
	int	i;

	is_n = 0;
	i = 1;
	if (!args[1])
		return (0);
	while (ft_isdashn(args[i]))
	{
		is_n = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		if ((is_n == 0 && i != 1) || (is_n == 1 && i != 2))
			write(STDOUT_FILENO, " ", 1);
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
	}
	if (is_n == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

