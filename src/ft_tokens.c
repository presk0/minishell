/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*													+:+ +:+			+:+	 */
/*   By: nidionis <nidionis@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#			 */
/*   Updated: 2025/01/17 15:19:11 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

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

int	substitute_var_in_token(t_list *gc, t_token *token)
{
}

t_token	*tokenize_cmd(t_list *gc, char *cmd, t_token *token)
{
	int	op;

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
		else if (!op && !is_quoted(*cmd, BUFF_TOK_CMD, SAVE)
			&& !ft_strchr(WHITE_SPACE, *cmd))
			cmd = save_token_cmd(gc, cmd, token);
		else
			cmd++;
	}
	substitute_var_in_token(gc, token);
	return (token);
}

void	print_token(t_token *token)
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
