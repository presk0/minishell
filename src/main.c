/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/30 15:40:45 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	minishell_exit(t_list *gc)
{
	rl_clear_history();
	gc_free_all(&gc);
	exit(-1);
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

void	apply_cmd(char *line, t_list *gc)
{
	t_btree			*cmd_tree;
	t_btree_content	*content;

	content = gc_malloc(&gc, 1, sizeof(t_btree_content));
	if (!content)
		minishell_exit(gc);
	content->cmd = line;
	content->token = NULL;
	cmd_tree = btree_create_node(content);
	btree_split(gc, cmd_tree, ft_strdup("|"));
	btree_split(gc, cmd_tree, ft_strdup("<<"));
	btree_split(gc, cmd_tree, ft_strdup(">>"));
	btree_split(gc, cmd_tree, ft_strdup("<"));
	btree_split(gc, cmd_tree, ft_strdup(">"));
	display_tree(cmd_tree, print_node_content);
	free_tree(cmd_tree, free_node_content);
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
	char	*line = ft_strdup(argv[1]);
	//minishell();
	apply_cmd(line, NULL);
	//printf("[substr_left] %s\n", substr_left(argv[1]));
	//printf("[substr_right] %s\n", substr_right(argv[1]));
	return (0);
}

