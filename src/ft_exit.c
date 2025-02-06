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

int	format_exit_status(int status)
{
	if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	else
		status = 128 + WTERMSIG(status);
	return (status);
}

void	minishell_exit(t_data *d, char *errmsg, int status)
{
	if (errmsg)
		perror(errmsg);
	if (status > 255)
		status = 154;
	rl_clear_history();
	gc_free_all(&d->gc);
	exit(status);
}

int	ft_exit(t_data *d, t_token *token)
{
	long int	exit_status;

	exit_status = ft_atoi_err(token->args[1]);
	if (exit_status > INT_MAX)
	{
		printf("bash: exit: %s: numeric argument required\n", \
														token->args[1]);
		exit_status = 0;
	}
	d->status = format_exit_status(exit_status);
	minishell_exit(d, "exit", d->status);
	return (0);
}
