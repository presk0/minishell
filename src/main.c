/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nkieffer <nkieffer@student.42.fr>			+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/23 23:43:03 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(char *errmsg, int status)
{
	if (errmsg)
		ft_errmsg(errmsg);
	rl_clear_history();
	//print_gc(d.gc);
	gc_free_all(&d.gc);
	exit(status);
}

char	**duplicate_tab(char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;
	size_t	i;

	tab_len = ft_tablen(tab_original);
	tab_copy = gc_malloc(&d.gc, (tab_len + 1), sizeof(char *));
	tab_copy[tab_len] = NULL;
	i = 0;
	while (i < tab_len)
	{
		tab_copy[i] = gc_strdup(&d.gc, tab_original[i]);
		if (!tab_copy[i])
		{
			ft_errmsg("[duplicate_tab]malloc error\n");
			minishell_exit("[duplicate_tab]", ERR_GC_STRDUP);
		}
		i++;
	}
	return (tab_copy);
}

void	minishell(char **envp)
{
	char	*line;

	init_sig();
	d.gc = NULL;
	d.status = 0;
	d.env = duplicate_tab(envp);
	d.sigint_received = 0;
	while (1)
	{
		line = readline(PS1);
		if (line == NULL)
			break ;
		if (gc_append(&d.gc, line))
		{
			run_line(line);
			add_history(line);
			gc_free_item(&d.gc, line);
		}
		else
		{
			ft_errmsg("[minishell] did not append to gc");
			minishell_exit("", ERR_GC_APPEND);
		}
	}
	minishell_exit("exit", CLEAN_EXIT);
}

t_data d;

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	minishell(envp);
	return (0);
}
