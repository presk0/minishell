/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <nidionis@student.42.fr>			+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/01/23 19:31:55 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

static char	*is_available_path(char *path_i, char *cmd)
{
	char	*tryed_path;
	char	*path;

	tryed_path = ft_strjoin(path_i, "/");
	path = NULL;
	if (tryed_path)
	{
		path = ft_strjoin(tryed_path, cmd);
		free(tryed_path);
		if (access(path, F_OK) == 0)
			return (path);
		else
			free(path);
	}
	return (NULL);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	path = NULL;
	if (paths[i])
		while (paths[i] && !path)
			path = is_available_path(paths[i++], cmd);
	ft_free_split(&paths);
	return (gc_append(&d.gc, path));
}

void	prepend_path(char **cmd)
{
	char	*path_available;

	if (!cmd)
		return ;
	path_available = find_path(*cmd, d.env);
	if (path_available)
	{
		gc_free_item(&d.gc, *cmd);
		*cmd = path_available;
	}
	else
	{
		if (*cmd)
			printf("%s: command not found\n", *cmd);
		gc_free_tree(d.gc, &d.cmd_tree, gc_free_node_content);
	}
}

char	*save_token_cmd(char *cmd, t_token *token)
{
	char	*itm;

	itm = strdup_wd_quote(cmd);
	if (itm)
	{
		if (!token->cmd)
			token->cmd = itm;
		if (*itm == '\0')
		{
			gc_free_item(&d.gc, itm);
			return (++cmd);
		}
		else
			append_tab(&(token->args), itm);
	}
	return (cmd + strlen_wd_quoted(cmd));
}

t_token	*tokenize_cmd(char *cmd, t_token *token)
{
	int	op;

	if (!token)
		return (NULL);
	is_quoted(0, BUFF_TOK_CMD, RESET);
	while (*cmd)
	{
		op = is_operand(cmd);
		if (op == -1)
			return (gc_free_item(&d.gc, token), NULL);
		if (op && !is_quoted(*cmd, BUFF_TOK_CMD, SAVE))
			cmd = save_token_op(cmd, op, token);
		else if (!op && !ft_strchr(WHITE_SPACE, *cmd))
			cmd = save_token_cmd(cmd, token);
		else
			cmd++;
	}
	substitute_var_in_token(token);
	prepend_path(&token->cmd);
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
