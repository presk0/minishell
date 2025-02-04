/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_exec_forked.c                                   :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 00:03:43 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

void	execve_node(t_data *d, t_btree *node)
{
	t_btree_content	*content;
	t_token			*token;

	if (!node)
		return ;
	content = node->content;
	token = &(content->token);
	forked_sig();
	execve(token->cmd, token->args, d->env);
	minishell_exit(d, token->cmd, CMD_NOT_FOUND);
}

int	exec_forking(t_data *d, t_btree *node)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		minishell_exit(d, "[exec_forking] fork failed", -1);
	if (pid == 0)
		execve_node(d, node);
	waitpid(pid, &d->status, 0);
	return (d->status);
}
