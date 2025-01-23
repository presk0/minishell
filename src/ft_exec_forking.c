/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_forking.c                                  :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/23 16:53:12 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	run_line(char *line)
{
	t_btree_content	*content;
	char			*line_cpy;

	if (!line || !*line)
		return ;
	content = gc_malloc(&d.gc, 1, sizeof(t_btree_content));
	if (!content)
		minishell_exit();
	line_cpy = ft_strdup(line);
	content->cmd = line_cpy;
	gc_append(&d.gc, line_cpy);
	d.cmd_tree = new_node(content);
	exec_whole_line(d.cmd_tree);
}


int	exec_whole_line()
{
	pid_t	pid;
	int		status;
	char	*sep;

	(void)pid;
	(void)status;
	sep = ft_strdup("|");
	gc_append(&d.gc, sep);
	btree_split(d.cmd_tree, sep);
	if (check_childs(d.cmd_tree))
	{
		rec_tokenization(d.cmd_tree);
		if (d.cmd_tree)
			rec_exec(d.cmd_tree);
	}
	gc_free_tree(d.gc, &d.cmd_tree, gc_free_node_content);
	// gc_free_item(&d.gc, sep);
	return (-1);
}
