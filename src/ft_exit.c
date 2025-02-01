/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/01 19:54:25 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(char *errmsg, int status)
{
	if (errmsg)
		perror(errmsg);
	else
		printf("exit\n");
	rl_clear_history();
	gc_free_all(&g_d.gc);
	exit(status);
}

int	ft_exit(t_token *token)
{
	long int	exit_status;

	exit_status = ft_atoi_err(token->args[1]);
	if (exit_status > 255)
	{
		if (exit_status > INT_MAX)
			printf("bash: exit: %s: numeric argument required\n", \
														token->args[1]);
		g_d.status = 0;
	}
	g_d.status = exit_status;
	minishell_exit(NULL, g_d.status);
	return (0);
}
