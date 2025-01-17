/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   template.c											:+:	  :+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#			 */
/*   Updated: 2024/09/05 14:15:32 by nidionis			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	open_redirect(char *file, int mode)
{
	int	fd;

	fd = open(file, mode, 0666);
	if (fd == -1)
	{
		perror("[open_redirect] Redirection failed");
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
}

void	handle_redir_out(t_token *tok)
{
	int	redir;
	int	mode;

	mode = tok->append_flag ? O_CREAT | O_WRONLY | O_APPEND : O_CREAT | O_WRONLY | O_TRUNC;
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
