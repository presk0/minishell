/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_recursive.c                                :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/24 14:02:52 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	execve_node(t_btree *node)
{
	t_btree_content	*content;
	t_token			*token;

	if (!node)
		return ;
	content = node->content;
	token = &(content->token);
	forked_sig();
	execve(token->cmd, token->args, g_d.env);
	minishell_exit(token->cmd, CMD_NOT_FOUND);
}

int	exec_forking(t_btree *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		minishell_exit("[exec_forking] fork failed", -1);
	if (pid == 0)
		execve_node(node);
	waitpid(pid, &g_d.status, 0);
	return (g_d.status);
}
