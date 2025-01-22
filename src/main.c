/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nkieffer <nkieffer@student.42.fr>			+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/22 11:14:44 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(char *errmsg, int status)
{
	if (errmsg)
		ft_errmsg(errmsg);
	rl_clear_history();
	gc_free_all(&d.gc);
	exit(status);
}

char	**duplicate_tab(char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;

	tab_len = ft_tablen(tab_original);
	tab_copy = gc_malloc(&d.gc, (tab_len + 1), sizeof(char *));
	tab_copy[tab_len] = NULL;
	while (tab_len--)
	{
		tab_copy[tab_len] = gc_strdup(&d.gc, tab_original[tab_len]);
		if (!tab_copy[tab_len])
		{
			printf("[duplicate_tab]malloc error\n");
			minishell_exit("", ERR_GC_STRDUP);
		}
	}
	return (tab_copy);
}

void	minishell(char **envp)
{
	char	*line;

	init_sig();
	d.env = duplicate_tab(envp);
	while (1)
	{
		line = readline(PS1);
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (gc_append(&d.gc, line))
		{
			run_line(line);
			add_history(line);
		}
		else
		{
			printf("[minishell] did not append to gc");
			minishell_exit("", ERR_GC_APPEND);
		}
	}
	minishell_exit("TADAAAAM!", CLEAN_EXIT);
}

t_data d;


int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	d.env = envp;
	printf("%s\n", rm_quotes(argv[1]));
	return (0);
}
