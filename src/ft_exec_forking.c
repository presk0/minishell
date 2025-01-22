/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_forking.c                                  :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/16 13:52:59 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	run_line(char *line)
{
	t_btree			*cmd_tree;
	t_btree_content	*content;
	char			*line_cpy;

	(void)cmd_tree;
	content = gc_malloc(&d.gc, 1, sizeof(t_btree_content));
	if (!content)
		minishell_exit();
	line_cpy = ft_strdup(line);
	content->cmd = line_cpy;
	gc_append(&d.gc, line_cpy);
	cmd_tree = new_node(content);
	exec_whole_line(cmd_tree);
}


int	exec_whole_line(t_btree *cmd_tree)
{
	pid_t	pid;
	int		status;
	char	*sep;

	(void)pid;
	(void)status;
	sep = ft_strdup("|");
	gc_append(&d.gc, sep);
	btree_split(cmd_tree, sep);
	if (check_childs(cmd_tree))
	{
		rec_tokenization(cmd_tree);
		rec_exec(cmd_tree);
	}
	gc_free_tree(d.gc, &cmd_tree, gc_free_node_content);
	// gc_free_item(&d.gc, sep);
	return (-1);
}
