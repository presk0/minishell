/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   template.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2024/09/05 14:15:32 by nidionis			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	is_operand(char *cmd)
{
	if (!ft_strncmp(cmd, "<<<", 3))
	{
		printf("bash: syntax error near unexpected token `<'");
		return (-1);
	}
	if (!ft_strncmp(cmd, ">>>", 3))
	{
		printf("bash: syntax error near unexpected token `>'");
		return (-1);
	}
	if (!ft_strncmp(cmd, "<<", 2))
		return (HERE_DOC);
	if (!ft_strncmp(cmd, ">>", 2))
		return (REDIR_APPEND);
	if (!ft_strncmp(cmd, "<", 1))
		return (REDIR_IN);
	if (!ft_strncmp(cmd, ">", 1))
		return (REDIR_OUT);
	return (0);
}

char	*skip_operand(char *cmd, char op)
{
	if (cmd)
	{
		while (*cmd == op)
			cmd++;
		while (*cmd && ft_strchr(WHITE_SPACE, *cmd))
			cmd++;
	}
	return (cmd);
}

char	*skip_op_and_arg(char *str, char op)
{
	str = skip_operand(str, op);
	return (str + strlen_wd_quoted(str));
}

char	*grep_token(char op, char *cmd)
{
	cmd = skip_operand(cmd, op);
	return (strdup_wd_quote(cmd));
}

char	*save_and_skip_redir_out(char *cmd, t_token *token)
{
	if (token->redir_out)
		gc_free_item(&g_d.gc, token->redir_out);
	token->redir_out = grep_token('>', cmd);
	token->append_flag = 0;
	return (skip_op_and_arg(cmd, '>'));
}

char	*save_and_skip_redir_in(char *cmd, t_token *token)
{
	token->redir_in = grep_token('<', cmd);
	token->heredoc = 0;
	return (skip_op_and_arg(cmd, '<'));
}

char	*save_and_skip_here_doc(char *cmd, t_token *token)
{
	token->redir_in = grep_token('<', cmd);
	token->heredoc = 1;
	return (skip_op_and_arg(cmd, '<'));
}

char	*save_and_skip_redir_append(char *cmd, t_token *token)
{
	if (token->redir_out)
		gc_free_item(&g_d.gc, token->redir_out);
	token->redir_out = grep_token('>', cmd);
	token->append_flag = 1;
	return (skip_op_and_arg(cmd, '>'));
}

char	*save_token_op(char *cmd, int op, t_token *token)
{
	if (op == REDIR_IN)
		return (save_and_skip_redir_in(cmd, token));
	if (op == REDIR_OUT)
		return (save_and_skip_redir_out(cmd, token));
	if (op == HERE_DOC)
		return (save_and_skip_here_doc(cmd, token));
	if (op == REDIR_APPEND)
		return (save_and_skip_redir_append(cmd, token));
	return (NULL);
}
