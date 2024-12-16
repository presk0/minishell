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

char	*substr_left(char *node_content)
{
	char	*ret;

	ret = ft_substr(node_content, 0, ft_strchr(node_content, '|') - node_content);
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}
char	*substr_right(char *node_content)
{
	char	*ret;

	ret = ft_substr(node_content, ft_strchr(node_content, '|') - node_content + 1, ft_strlen(node_content));
	if (ret && !*ret)
	{
		free(ret);
		ret = NULL;
	}
	return (ret);
}
void	*pipe_split(t_btree *node)
{
	t_btree	*left;
	t_btree	*right;
	char	*left_content;
	char	*right_content;
	char	*node_content;

	if (!node)
		return (NULL);
	left = NULL;
	right = NULL;
	node_content = (char *)node->content;
 	if (!ft_strchr(node_content, '|'))
		return (NULL);
	left_content = substr_left(node_content);
	right_content = substr_right(node_content);
	if (left_content)
		left = btree_create_node(left_content);
	if (right_content)
		right = btree_create_node(right_content);
	if (node->left)
		ft_errmsg("[pipe_split] create left node but one already exists\n");
	node->left = left;
	if (node->right)
		ft_errmsg("[pipe_split] create right node but one already exists\n");
	node->right = right;
	if (node_content)
	{
		*node_content = '|';
		node_content[1] = '\0';
	}
	return (NULL);
}

//void	*btree_pipe_split(t_btree *root, char c)
//{
//    btree_split_node(*root, pipe_split);
//}

void	apply_cmd(char *line, t_list *gc)
{
	t_btree	*cmd_tree;
	(void)gc;

	cmd_tree = btree_create_node(line);
	btree_apply_prefix(cmd_tree, pipe_split);
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

