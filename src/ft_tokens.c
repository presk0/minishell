/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/03 21:59:07 by nidionis         ###   ########.fr       */
/*                                                                            */
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

int	strlen_wd_quoted(char *cmd)
{
	int	len;

	is_quoted(0, BUFF_STRLEN, RESET);
	len = 0;
	while (*cmd)
	{
		if (!is_quoted(*cmd, BUFF_STRLEN, SAVE))
			if (is_operand(cmd) || ft_strchr(WHITE_SPACE, *cmd))
				break ;
		cmd++;
		len++;
	}
	return (len);
}

char	*strdup_wd_quote(t_list *gc, char *cmd)
{
	int		wd_len_quoted;
	char	*duplicated;
	char	*out;

	wd_len_quoted = strlen_wd_quoted(cmd);
	duplicated = gc_malloc(&gc, 1, wd_len_quoted + 1);
	if (!duplicated)
		return (NULL);
	out = duplicated;
	while (wd_len_quoted--)
		*duplicated++ = *cmd++;
	*duplicated = '\0';
	return (out);
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

char	*grep_token(t_list *gc, char op, char *cmd)
{
	cmd = skip_operand(cmd, op);
	return (strdup_wd_quote(gc, cmd));
}

/* creer et fermer les redir out */
char	*save_token_op(t_list *gc, char *cmd, int op, t_token *token)
{
	if (op == REDIR_IN)
	{
		if (token->redir_in)
			gc_free_item(&gc, token->redir_in);
		token->redir_in = grep_token(gc, '<', cmd);
		token->heredoc = 0;
		return (skip_op_and_arg(cmd, '<'));
	}
	if (op == REDIR_OUT)
	{
		if (token->redir_out)
			gc_free_item(&gc, token->redir_out);
		if (token->redir_out)
			gc_free_item(&gc, token->redir_out);
		token->redir_out = grep_token(gc, '>', cmd);
		token->append_flag = 0;
		return (skip_op_and_arg(cmd, '>'));
	}
	if (op == HERE_DOC)
	{
		token->redir_in = grep_token(gc, '<', cmd);
		token->heredoc = 1;
		return (skip_op_and_arg(cmd, '<'));
	}
	if (op == REDIR_APPEND)
	{
		if (token->redir_out)
			gc_free_item(&gc, token->redir_out);
		token->redir_out = grep_token(gc, '>', cmd);
		token->append_flag = 1;
		return (skip_op_and_arg(cmd, '>'));
	}
	return (NULL);
}

/*
t_token	*init_token(t_list *gc)
{
	t_token *token;

	token = gc_malloc(&gc, sizeof(t_token), 1);
	if (!token)
		return (NULL);
	token->cmd = NULL;
	token->arg = NULL;
	token->redir_in	= NULL;
	token->redir_out = NULL;
	token->append_flag = 0;
	token->heredoc = 0;
	return (token);
}
*/

t_token	*tokenize_cmd(t_list *gc, char *cmd)
{
	t_token *token;
	int		op;

	token = gc_malloc(&gc, sizeof(t_token), 1);
	if (!token)
		return (NULL);
	is_quoted(0, BUFF_TOK_CMD, RESET);
	while (*cmd)
	{
		op = is_operand(cmd);
		if (op == -1)
			return (gc_free_item(&gc, token), NULL);
		if (op && !is_quoted(*cmd, BUFF_TOK_CMD, SAVE))
			cmd = save_token_op(gc, cmd, op, token);
		//else if (!op && !token->cmd && !is_quoted(*cmd, BUFF_TOK_CMD, SAVE))
		//	cmd = save_token_cmd(gc, cmd, op, token);
		else
			cmd++;
	}
	return (token);	
}

void	print_token(t_token	*token)
{
	if (!token)
		return ;
	printf("cmd: {%s}\n", token->cmd);
	if (token->arg)
	{
		while (token->arg)
			printf("cmd: {%s}\n", *(token->arg)++);
	}
	printf("redir_in: {%s}\n", token->redir_in);
	printf("redir_out: {%s}\n", token->redir_out);
	printf("append_flag: {%i}\n", token->append_flag);
	printf("heredoc: {%i}\n", token->heredoc);
}
