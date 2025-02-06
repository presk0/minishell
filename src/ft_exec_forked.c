/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/02/04 01:57:19 by nidionis         ###   ########.fr       */
/*                                                                            */
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
	sig_default();
	execve(token->cmd, token->args, d->env);
	minishell_exit(d, token->cmd, CMD_NOT_FOUND);
}

int	exec_forking(t_data *d, t_btree *node)
{
	pid_t	pid;

	sig_ignores();
	pid = fork();
	if (pid == -1)
		minishell_exit(d, "[exec_forking] fork failed", -1);
	if (pid == 0)
		execve_node(d, node);
	waitpid(pid, &d->status, 0);
	d->status = format_exit_status(d->status);
	if (d->status == 131)
		ft_errmsg("Quit\n");
	init_sig(d);
	return (d->status);
}
