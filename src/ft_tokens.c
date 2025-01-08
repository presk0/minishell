/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/04 16:35:12 by nidionis         ###   ########.fr       */
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

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (*tab++)
			i++;
	return (i);
}

void	append_tab(t_list *gc, char ***tab_addr, char *str)
{
	size_t	len;
	char	**tab;
	char	**new_tab;

	tab = *tab_addr;
	len = ft_tablen(tab) + 1;
	if (!tab)
		new_tab = gc_malloc(&gc, sizeof(char *), 2);
	else
		new_tab = gc_malloc(&gc, sizeof(char *), len);
	if (!new_tab)
	{
		printf("[append_tab]malloc error\n");
		minishell_exit(gc);
	}
	new_tab[len--] = NULL;
	new_tab[len] = str;
	if (tab)
	{
		while (len--)
			new_tab[len] = tab[len];
		gc_free_item(&gc, tab);
	}
	*tab_addr = new_tab;
}

char	*save_token_cmd(t_list *gc, char *cmd, t_token *token)
{
	char	*itm;

	itm = strdup_wd_quote(gc, cmd);
	if (itm)
	{
		if (!token->cmd)
			token->cmd = itm;
		if (*itm == '\0')
		{
			gc_free_item(&gc, itm);
			return (++cmd);
		}
		else
			append_tab(gc, &(token->args), itm);
	}
	return (cmd + strlen_wd_quoted(cmd));
}

t_token	*tokenize_cmd(t_list *gc, char *cmd, t_token *token)
{
	//t_token *token;
	int		op;

	//token = gc_malloc(&gc, sizeof(t_token), 1);
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
		else if (!op && !is_quoted(*cmd, BUFF_TOK_CMD, SAVE) && !ft_strchr(WHITE_SPACE, *cmd))
			cmd = save_token_cmd(gc, cmd, token);
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
	if (token->args)
	{
		while (*(token->args))
			printf("	args: {%s}\n", *(token->args)++);
	}
	printf("redir_in: {%s}\n", token->redir_in);
	printf("redir_out: {%s}\n", token->redir_out);
	printf("append_flag: {%i}\n", token->append_flag);
	printf("heredoc: {%i}\n", token->heredoc);
}
