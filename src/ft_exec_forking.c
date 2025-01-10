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

void	apply_cmd(t_list *gc, char *line)
{
	t_btree			*cmd_tree;
	t_btree_content	*content;

	(void)cmd_tree;
	content = gc_malloc(&gc, 1, sizeof(t_btree_content));
	if (!content)
		minishell_exit(gc);
	content->cmd = ft_strdup(line);
	gc_append(&gc, content->cmd);
	cmd_tree = new_node(gc, content);
	exec_forking(gc, cmd_tree, NULL);
}

void	exec_forking(t_list *gc, t_btree *cmd_tree, char **envp)
{
	pid_t pid;
	int status;
	char			*sep;

	pid = fork();
	if (pid == -1) {
		perror("[exec_forking] fork failed");
		minishell_exit(gc);
	}
	if (pid == 0) {
		init_sig(gc);
		sep = ft_strdup("|");
		gc_append(&gc, sep);
		btree_split(gc, cmd_tree, sep);
		if (!check_childs(gc, cmd_tree)) 
			return ;
		rec_tokenization(gc, cmd_tree, NULL);
		rec_exec(gc, cmd_tree, envp);
		gc_free_tree(&gc, &cmd_tree, gc_free_node_content);
		gc_free_item(&gc, sep);
		exit(0);
	}
	waitpid(pid, &status, 0);
}
