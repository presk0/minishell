/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   template.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2024/09/05 14:15:32 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	run_line(t_list *gc, char *line, t_env *env)
{
	t_btree			*cmd_tree;
	t_btree_content	*content;
	char			*line_cpy;

	(void)cmd_tree;
	content = gc_malloc(&gc, 1, sizeof(t_btree_content));
	if (!content)
		minishell_exit(gc);
	line_cpy = ft_strdup(line);
	content->cmd = line_cpy;
	gc_append(&gc, line_cpy);
	cmd_tree = new_node(gc, content);
	exec_forking(gc, cmd_tree, env);
}

void	exec_forking(t_list *gc, t_btree *cmd_tree, t_env *env)
{
	pid_t pid;
	int status;
	char			*sep;

	(void)pid;
	(void)status;
	sep = ft_strdup("|");
	gc_append(&gc, sep);
	btree_split(gc, cmd_tree, sep);
	if (check_childs(gc, cmd_tree)) 
	{
		rec_tokenization(gc, cmd_tree, env);
//		pid = fork();
//		if (pid == -1) {
//			perror("[exec_forking] fork failed");
//			minishell_exit(gc);
//		}
//		if (pid == 0) {
//			init_sig(gc);
			rec_exec(gc, cmd_tree, env);
//			exit(-42);
//		}
//		waitpid(pid, &status, 0);
	}
	gc_free_tree(&gc, &cmd_tree, gc_free_node_content);
	//gc_free_item(&gc, sep);
}
