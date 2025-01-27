/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/26 00:54:04 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	open_redirect(char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0666);
	if (fd == -1)
	{
		perror(file);
		return (-1);
	}
	return (fd);
}

void	handle_redir_in(t_token *tok)
{
	int	redir;
	int	mode;

	mode = O_RDONLY;
	if (tok->redir_in && !tok->heredoc)
	{
		redir = open_redirect(tok->redir_in, mode);
		if (redir != -1)
		{
			dup2(redir, STDIN_FILENO);
			close(redir);
		}
	}
	else if (tok->heredoc)
	{
		if (handle_heredoc(tok->redir_in) == -1)
			ft_errmsg("Error: Failed to handle heredoc\n");
	}
}

int	handle_eoheredoc(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (-1);
}

void	handle_redir_out(t_token *tok)
{
	int	redir;
	int	mode;

	if (tok->append_flag)
		mode = O_CREAT | O_WRONLY | O_APPEND;
	else
		mode = O_CREAT | O_WRONLY | O_TRUNC;
	if (tok->redir_out)
	{
		redir = open_redirect(tok->redir_out, mode);
		if (redir != -1)
		{
			dup2(redir, STDOUT_FILENO);
			close(redir);
		}
	}
}
