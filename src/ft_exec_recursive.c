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

void	execute_command(t_btree *node)
{
	t_token	*tok;
	int		saved_std[3];

	tok = &(((t_btree_content *)(node->content))->token);
	save_stds(saved_std);
	handle_redir_in(tok);
	handle_redir_out(tok);
	if (is_builtin(tok))
		exec_builtin_scotch(node);
	else
		exec_forking(node);
	restore_stds(saved_std);
}

void	rec_exec(t_btree *node)
{
	int	pipe_fd[2];
	int	stdin_fd;

	stdin_fd = dup(STDIN_FILENO);
	handle_dup_failure(stdin_fd, "[rec_exec] dup failed");
	if (is_pipe(node))
	{
		handle_pipe_failure(pipe(pipe_fd), "[rec_exec] pipe failed");
		if (fork() == 0)
		{
			close(pipe_fd[0]);
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[1]);
			rec_exec(node->left);
			exit(EXIT_SUCCESS);
		}
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		rec_exec(node->right);
	}
	else
		execute_command(node);
	reset_stdin(stdin_fd);
	close(stdin_fd);
}
