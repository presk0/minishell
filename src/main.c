/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2025/01/03 17:17:06 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(t_list *gc)
{
	rl_clear_history();
	gc_free_all(&gc);
	exit(0);
}

char	*end_of_word(char *str)
{
	if (str)
		while (*str && (ft_isalnum(*str) || *str == '_'))
			str++;
	return (str);
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


void	minishell(void)
{
	char	*line;
	t_list	*gc;

	gc = NULL;
	init_sig(gc);
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
			apply_cmd(gc, line);
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

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	//t_list	*gc = NULL;
	//char	*line = ft_strdup(argv[1]);
	//gc_append(&gc, line);
	//apply_cmd(gc, line);
	//minishell_exit(gc);
	minishell();
	return (0);
}