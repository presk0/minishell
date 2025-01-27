/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nkieffer <nkieffer@student.42.fr>			+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 13:34:45 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(char *errmsg, int status)
{
	if (errmsg)
		perror(errmsg);
	else
		printf("exit\n");
	rl_clear_history();
	// print_gc(g_d.gc);
	gc_free_all(&g_d.gc);
	exit(status);
}

char	**ft_duplicate_tab(char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;
	size_t	i;

	tab_len = ft_tablen(tab_original);
	tab_copy = malloc((tab_len + 1) * sizeof(char *));
	tab_copy[tab_len] = NULL;
	i = 0;
	while (i < tab_len)
	{
		tab_copy[i] = ft_strdup(tab_original[i]);
		if (!tab_copy[i])
		{
			ft_errmsg("[duplicate_tab]malloc error\n");
			minishell_exit("[duplicate_tab]", ERR_GC_STRDUP);
		}
		i++;
	}
	return (tab_copy);
}

char	**duplicate_tab(char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;
	size_t	i;

	tab_len = ft_tablen(tab_original);
	tab_copy = gc_malloc(&g_d.gc, (tab_len + 1), sizeof(char *));
	tab_copy[tab_len] = NULL;
	i = 0;
	while (i < tab_len)
	{
		tab_copy[i] = gc_strdup(&g_d.gc, tab_original[i]);
		if (!tab_copy[i])
		{
			ft_errmsg("[duplicate_tab]malloc error\n");
			minishell_exit("[duplicate_tab]", ERR_GC_STRDUP);
		}
		i++;
	}
	return (tab_copy);
}

void	inc_shlvl(void)
{
	int		shlvl;
	char	*shlvl_str;
	char	*shlvl_line;

	shlvl_str = ft_getenv("SHLVL");
	shlvl = ft_atoi(shlvl_str);
	shlvl++;
	shlvl_str = ft_itoa(shlvl);
	shlvl_line = gc_strdup(&g_d.gc, "SHLVL=");
	gc_strcat(&g_d.gc, &shlvl_line, shlvl_str);
	free(shlvl_str);
	ft_setenv(shlvl_line);
}

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
		if (line == NULL)
			break ;
		if (gc_append(&g_d.gc, line))
		{
			run_line(line);
			add_history(line);
			gc_free_item(&g_d.gc, line);
		}
		else
		{
			ft_errmsg("[minishell] did not append to gc");
			minishell_exit("", ERR_GC_APPEND);
		}
	}
	minishell_exit(NULL, CLEAN_EXIT);
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
	// g_d.gc = NULL;
	// g_d.status = 0;
	// g_d.env = duplicate_tab(envp);
	// g_d.sigint_received = 0;
	// static t_token token;
	// char *line = gc_strdup(&g_d.gc, argv[1]);
	return (0);
}
