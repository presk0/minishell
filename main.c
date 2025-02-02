/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:24:39 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/02 23:15:54 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
char	*rl_quoted()
{
	char	*line;
	char	*closed_line;
	char	prompt[1024];
	int		quote;

	quote = SIMPLE_QUOTE;
	closed_line = NULL;
	line = "Un spaghetti parfaitement droit.";
	ft_strlcpy(prompt, PS1, strlen(PS1) + 1);
	while (quote && line)
	{
		line = readline(prompt);
		if (gc_append(&g_d.gc, line))
		{
			gc_strcat(&g_d.gc, &closed_line, line);
			gc_free_item(&g_d.gc, line);
			quote = is_quote_opened(closed_line);
			if (quote)
				ft_strlcpy(prompt, "> ", 3);
		}
	}
	return (closed_line);
}
*/

void	minishell(char **envp)
{
	char	*line;

	init_sig();
	g_d.gc = NULL;
	g_d.status = 0;
	g_d.env = duplicate_tab(envp);
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
