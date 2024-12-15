/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/15 19:17:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(t_list *gc)
{
	rl_clear_history();
	clean_exit(&gc);
}

char	*end_of_word(char *str)
{
	if (str)
		while (*str && (ft_isalnum(*str) || *str == '_'))
			str++;
	return (str);
}

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

// char	*substitute_vars(char *str, t_list *gc)
// {
// 	char	*new_str;
// 	char	*tmp;
// 	size_t	len_max;
// 	size_t	i;

// 	len_max = ft_strlen(str) * 2 + 1024;
// 	if (!str)
// 		return (NULL);
// 	new_str = NULL;
// 	new_str = gc_calloc(&gc, len_max, sizeof(char));
// 	if (!new_str)
// 		minishell_exit(gc);
// 	i = 0;
// 	while (*str)
// 	{
// 		if (i >= len_max)
// 		{
// 			tmp = gc_calloc(&gc, len_max, sizeof(char));
// 			if (!tmp)
// 				minishell_exit(gc);
// 			ft_strlcpy(tmp, new_str, len_max);
// 			gc_free_item(&gc, new_str);	
// 			new_str = tmp;
// 		}
// 		if (*str == '$')
// 		{
// 			ft_strlcat(new_str, str, len_max);
// 			i += substitute_var(new_str + i, gc);
// 			str = end_of_word(++str);
// 		}
// 		else
// 			new_str[i++] = *str++;
// 	}
// 	return (new_str);
// }

void	*split_pipes(void *content, int	POS)
{
	size_t	i;
	char	*str;

	str = (char *)content;
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '|')
		i++;
	if (POS == LEFT)
		return (ft_substr(str, 0, i));
	else if (POS == RIGHT)
		return (ft_substr(str, i + 1, ft_strlen(str)));
	strcpy(content, "|");
	return (NULL);
}

void	apply_cmd(char *line, t_list *gc)
{
	t_btree	*cmd_tree;

	cmd_tree = btree_create_node(line);
	btree_split_node(cmd_tree, split_pipes);
	gc_append(&gc, cmd_tree);
	display_tree(cmd_tree);
}

void	minishell(void)
{
	char	*line;
	t_list	*gc;

	gc = NULL;
	while (1)
	{
	    line = readline(PS1);
	    if (line == NULL)
	    {
			printf("Error reading input or EOF encountered.\n");
			return ;
	    }
	    gc_append(&gc, line);
	    apply_cmd(line, gc);
	    add_history(line);
	    gc_free_item(&gc, line);
	}
	minishell_exit(gc);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	//minishell();
	apply_cmd(argv[1], NULL);
	printf("%s\n", argv[0]);
	return (0);
}

