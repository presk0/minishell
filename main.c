/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:24:39 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 01:59:36 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*rl_quoted(t_data *d)
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
		if (gc_append(&d->gc, line))
		{
			gc_strcat(&d->gc, &closed_line, line);
			gc_free_item(&d->gc, line);
			quote = is_quote_opened(closed_line);
			if (quote)
				ft_strlcpy(prompt, "> ", 3);
		}
	}
	return (closed_line);
}

void	minishell(char **envp)
{
	char	*line;
	t_data	d;

	d.gc = NULL;
	d.status = 0;
	d.env = duplicate_tab(&d, envp);
	inc_shlvl(&d);
	while (1)
	{
		init_sig(&d);
		line = rl_quoted(&d);
		if (!line)
			minishell_exit(&d, NULL, 0);
		g_child_opened = 0;
		run_line(&d, line);
		add_history(line);
		gc_free_item(&d.gc, line);
	}
}

void	print_tab(char **tab)
{
	if (tab)
		while (*tab)
			printf("%s\n", *tab++);
}

int	g_child_opened;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	minishell(envp);
	return (0);
}
