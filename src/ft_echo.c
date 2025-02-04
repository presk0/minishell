/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/03 22:43:06 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_echo(t_data *d, t_token *token)
{
	int	newline;
	int	i;

	newline = TRUE;
	i = 1;
	if (token->args[1] != NULL && ft_strcmp(token->args[1], "-n") == 0)
	{
		newline = FALSE;
		i++;
	}
	while (token->args[i] != NULL)
	{
		write(STDOUT_FILENO, token->args[i], ft_strlen(token->args[i]));
		if (token->args[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	d->status = CLEAN_EXIT;
	return (CLEAN_EXIT);
}
