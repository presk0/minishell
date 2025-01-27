/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_forking.c                                  :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 12:50:16 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	run_line(char *line)
{
	t_btree_content	*content;
	char			*line_cpy;

	if (!line || !*line)
		return ;
	content = gc_malloc(&g_d.gc, 1, sizeof(t_btree_content));
	if (!content)
		minishell_exit("[run_line]", -1);
	line_cpy = ft_strdup(line);
	content->cmd = line_cpy;
	gc_append(&g_d.gc, line_cpy);
	g_d.cmd_tree = new_node(content);
	exec_whole_line();
}

int	exec_whole_line(void)
{
	pid_t	pid;
	int		status;
	char	*sep;

	(void)pid;
	(void)status;
	sep = gc_strdup(&g_d.gc, "|");
	btree_split(g_d.cmd_tree, sep);
	if (check_childs(g_d.cmd_tree))
	{
		rec_tokenization(g_d.cmd_tree);
		if (g_d.cmd_tree)
			rec_exec(g_d.cmd_tree);
	}
	gc_free_tree(g_d.gc, &g_d.cmd_tree, gc_free_node_content);
	gc_free_item(&g_d.gc, sep);
	return (-1);
}
