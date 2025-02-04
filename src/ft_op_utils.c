/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/03 22:12:07 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*save_and_skip_redir_out(t_data *d, char *cmd, t_token *token)
{
	if (token->redir_out)
		gc_free_item(&d->gc, token->redir_out);
	token->redir_out = grep_token('>', cmd);
	token->append_flag = 0;
	return (skip_op_and_arg(cmd, '>'));
}

char	*save_and_skip_redir_in(t_data *d, char *cmd, t_token *token)
{
	if (token->redir_in)
		gc_free_item(&d->gc, token->redir_out);
	token->redir_in = grep_token('<', cmd);
	token->heredoc = 0;
	return (skip_op_and_arg(cmd, '<'));
}

char	*save_and_skip_here_doc(t_data *d, char *cmd, t_token *token)
{
	if (token->redir_in)
		gc_free_item(&d->gc, token->redir_out);
	token->redir_in = grep_token('<', cmd);
	token->heredoc = 1;
	return (skip_op_and_arg(cmd, '<'));
}

char	*save_and_skip_redir_append(t_data *d, char *cmd, t_token *token)
{
	if (token->redir_out)
		gc_free_item(&d->gc, token->redir_out);
	token->redir_out = grep_token('>', cmd);
	token->append_flag = 1;
	return (skip_op_and_arg(cmd, '>'));
}

char	*save_token_op(t_data *d, char *cmd, int op, t_token *token)
{
	if (op == REDIR_IN)
		return (save_and_skip_redir_in(d, cmd, token));
	if (op == REDIR_OUT)
		return (save_and_skip_redir_out(d, cmd, token));
	if (op == HERE_DOC)
		return (save_and_skip_here_doc(d, cmd, token));
	if (op == REDIR_APPEND)
		return (save_and_skip_redir_append(d, cmd, token));
	return (NULL);
}
