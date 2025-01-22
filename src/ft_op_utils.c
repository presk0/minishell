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

/* creer et fermer les redir out */
char	*save_token_op(char *cmd, int op, t_token *token)
{
	if (op == REDIR_IN)
	{
		if (token->redir_in)
			gc_free_item(&d.gc, token->redir_in);
		token->redir_in = grep_token('<', cmd);
		token->heredoc = 0;
		return (skip_op_and_arg(cmd, '<'));
	}
	if (op == REDIR_OUT)
	{
		if (token->redir_out)
			gc_free_item(&d.gc, token->redir_out);
		if (token->redir_out)
			gc_free_item(&d.gc, token->redir_out);
		token->redir_out = grep_token('>', cmd);
		token->append_flag = 0;
		return (skip_op_and_arg(cmd, '>'));
	}
	if (op == HERE_DOC)
	{
		token->redir_in = grep_token('<', cmd);
		token->heredoc = 1;
		return (skip_op_and_arg(cmd, '<'));
	}
	if (op == REDIR_APPEND)
	{
		if (token->redir_out)
			gc_free_item(&d.gc, token->redir_out);
		token->redir_out = grep_token('>', cmd);
		token->append_flag = 1;
		return (skip_op_and_arg(cmd, '>'));
	}
	return (NULL);
}
