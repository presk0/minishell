/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:24:39 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/28 00:37:32 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell(char **envp)
{
	char	*line;

	init_sig();
	g_d.gc = NULL;
	g_d.status = 0;
	g_d.env = duplicate_tab(envp);
	g_d.sigint_received = 0;
	inc_shlvl();
	while (1)
	{
		line = readline(PS1);
		if (gc_append(&g_d.gc, line))
		{
			run_line(line);
			add_history(line);
			gc_free_item(&g_d.gc, line);
		}
		else
			minishell_exit(NULL, ERR_GC_APPEND);
	}
}

t_data	g_d;

void	print_tab(char **tab)
{
	if (tab)
		while (*tab)
			printf("%s\n", *tab++);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	minishell(envp);
	return (0);
}
