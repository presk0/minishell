/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/15 21:49:12 by nidionis         ###   ########.fr       */
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

char	*substr_left(char *node_content, char *found)
{
	char	*ret;

	ret = ft_substr(node_content, 0, found - node_content);
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}
char	*substr_right(char *node_content, char *found)
{
	char	*ret;

	(void)node_content;
	while (found[0] == found[1])
		found++;
	found++;
	ret = ft_substr(found, 0, ft_strlen(found));
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}

void	split_node(t_btree *root, char *sep)
{
	char	*str;
	char	*found;

	if (root->left || root->right)
		return ;
	str = root->content;
	found = ft_strnstr(str, sep, ft_strlen(str));
	if (found)
	{
		root->left = btree_create_node(substr_left(str, found));
		root->right = btree_create_node(substr_right(str, found));
		root->content = ft_strdup(sep);
		free(str);
		str = NULL;
	}
}

void	btree_split(t_btree *root, char *sep)
{
	if (!root)
		return ;
	split_node(root, sep);
	if (root->left)
		btree_split(root->left, sep);
	if (root->right)
		btree_split(root->right, sep);
}

void	apply_cmd(char *line, t_list *gc)
{
	t_btree	*cmd_tree;
	(void)gc;

	cmd_tree = btree_create_node(line);
	btree_split(cmd_tree, "|");
	btree_split(cmd_tree, "<<<");
	btree_split(cmd_tree, "<<");
	btree_split(cmd_tree, ">>");
	btree_split(cmd_tree, "<");
	btree_split(cmd_tree, ">");
	display_tree(cmd_tree);
	free_tree(cmd_tree, free);
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

