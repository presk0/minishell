/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/02 20:38:21 by nidionis         ###   ########.fr       */
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

char	*save_token(t_list *gc, char *cmd, int op, t_token *token)
{
	(void)gc;
	(void)cmd;
	(void)op;
	(void)token;
	return (NULL);
}

t_token	*tokenize_cmd(t_list *gc, char *cmd)
{
	t_token *token;
	int		op;

	token = gc_malloc(&gc, sizeof(t_token), 1);
	if (!token)
		return (NULL);
	is_quoted(0, RESET);
	while (*cmd)
	{
		op = is_operand(cmd);
		if (op == -1)
			return (gc_free_item(&gc, token), NULL);
		if (op && !is_quoted(*cmd, SAVE))
			cmd = save_token(gc, cmd, op, token);
		else
			cmd++;
	}
	return (token);	
}
