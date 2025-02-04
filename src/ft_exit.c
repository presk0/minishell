/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:08:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(t_data *d, char *errmsg, int status)
{
	if (errmsg)
		perror(errmsg);
	else
		printf("exit\n");
	if (status > 255)
		status = -1;
	rl_clear_history();
	gc_free_all(&d->gc);
	exit(status);
}

int	ft_exit(t_data *d, t_token *token)
{
	long int	exit_status;

	exit_status = ft_atoi_err(token->args[1]);
	if (exit_status > 255)
	{
		if (exit_status > INT_MAX)
			printf("bash: exit: %s: numeric argument required\n", \
														token->args[1]);
		d->status = 0;
	}
	d->status = (int)exit_status;
	minishell_exit(d, NULL, d->status);
	return (0);
}
