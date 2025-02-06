/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op_grep_skip.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 01:40:23 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operand(char *cmd)
{
	if (!ft_strncmp(cmd, "<<<", 3))
	{
		ft_errmsg("bash: syntax error near unexpected token `<'\n");
		return (-1);
	}
	if (!ft_strncmp(cmd, ">>>", 3))
	{
		ft_errmsg("bash: syntax error near unexpected token `>'\n");
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

char	*grep_token(t_data *d, char op, char *cmd)
{
	cmd = skip_operand(cmd, op);
	return (strdup_wd_quote(d, cmd));
}
