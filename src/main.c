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


void	minishell(char **envp)
{
	char	*line;
	t_list	*gc;
	t_env	*env;

	gc = NULL;
	init_sig(gc);
	env = init_env(envp);
	if (!gc_append(&gc, env))
		minishell_exit(gc);
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
	//t_list	*gc = NULL;
	//char	*line = ft_strdup(argv[1]);
	//gc_append(&gc, line);
	//run_line(gc, line);
	//minishell_exit(gc);
	minishell(envp);
	return (0);
}