/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_forking.c                                  :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 14:31:07 by nidionis         ###   ########.fr       */
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
		minishell_exit("[run_line]", -1);
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
	sep = gc_strdup(&d.gc, "|");
	btree_split(d.cmd_tree, sep);
	if (check_childs(d.cmd_tree))
	{
		rec_tokenization(d.cmd_tree);
		if (d.cmd_tree)
			rec_exec(d.cmd_tree);
	}
	gc_free_tree(d.gc, &d.cmd_tree, gc_free_node_content);
	gc_free_item(&d.gc, sep);
	return (-1);
}
