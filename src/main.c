/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nkieffer <nkieffer@student.42.fr>			+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/16 11:54:36 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(t_list *gc)
{
	rl_clear_history();
	gc_free_all(&gc);
	exit(0);
}

/*
size_t	substitute_var(char *str, t_list *gc)
{
	char	*tmp;
	char	*var_value;

	if (!str)
		return (0);
	tmp = end_of_word(str + 1);
	var_value = ft_substr(str, 1, tmp - str);
	if (!var_value)
		return (0);
	tmp = getenv(var_value);
	gc_free_item(&gc, var_value);
	ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	return (ft_strlen(tmp));
}
*/

char	**duplicate_tab(t_list *gc, char **tab_original)
{
	char	**tab_copy;
	size_t	tab_len;

	tab_len = ft_tablen(tab_original);
	tab_copy = gc_malloc(&gc, (tab_len + 1), sizeof(char *));
	tab_copy[tab_len] = NULL;
	while (tab_len--)
	{
		tab_copy[tab_len] = gc_strdup(&gc, tab_original[tab_len]);
		if (!tab_copy[tab_len])
		{
			printf("[duplicate_tab]malloc error\n");
			minishell_exit(gc);
		}
	}
	return (tab_copy);
}

void	minishell(char **envp)
{
	char	*line;
	t_list	*gc;
	char	**env;

	gc = NULL;
	init_sig(gc);
	env = duplicate_tab(gc, envp);
	while (1)
	{
		line = readline(PS1);
		if (line == NULL)
		{
			printf("exit\n");
			break ;
		}
		if (gc_append(&gc, line))
		{
			run_line(gc, line, env);
			add_history(line);
		}
		else
		{
			printf("[minishell] did not append to gc");
			minishell_exit(gc);
		}
	}
	minishell_exit(gc);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	// t_list	*gc = NULL;
	// char	*line = ft_strdup(argv[1]);
	// gc_append(&gc, line);
	// run_line(gc, line);
	// minishell_exit(gc);
	minishell(envp);
	return (0);
}
