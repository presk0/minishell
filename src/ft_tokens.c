/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 00:10:34 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 01:42:58 by nidionis         ###   ########.fr       */
/*                                                                            */
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

static char	*find_path(t_data *d, char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (!cmd)
		return (NULL);
	if (ft_strncmp(cmd, "/", 1) == 0)
		if (access(cmd, F_OK) == 0)
			return (gc_strdup(&d->gc, cmd));
	if (ft_strncmp(cmd, "./", 2) == 0)
		return (gc_strdup(&d->gc, cmd));
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = NULL;
	if (envp && envp[i])
		paths = ft_split(envp[i] + 5, ':');
	i = 0;
	path = NULL;
	if (paths && paths[i])
		while (paths[i] && !path)
			path = is_available_path(paths[i++], cmd);
	ft_free_split(&paths);
	return (gc_append(&d->gc, path));
}

void	prepend_path(t_data *d, char **cmd)
{
	char	*path_available;

	if (!cmd)
		return ;
	path_available = find_path(d, *cmd, d->env);
	if (path_available)
	{
		gc_free_item(&d->gc, *cmd);
		*cmd = path_available;
	}
	else
	{
		if (*cmd)
			printf("%s: command not found\n", *cmd);
		gc_free_tree(d->gc, &d->cmd_tree, gc_free_node_content);
		d->status = CMD_NOT_FOUND;
	}
}

char	*save_token_cmd(t_data *d, char *cmd, t_token *token)
{
	char	*itm;

	itm = strdup_wd_quote(d, cmd);
	if (itm)
	{
		if (!token->cmd)
			token->cmd = itm;
		if (*itm == '\0')
		{
			gc_free_item(&d->gc, itm);
			return (++cmd);
		}
		else
			append_tab(d, &(token->args), itm);
	}
	return (cmd + strlen_wd_quoted(cmd));
}

t_token	*tokenize_cmd(t_data *d, char *cmd, t_token *token)
{
	int	op;

	if (!token)
		return (NULL);
	is_quoted(0, BUFF_TOK_CMD, RESET);
	while (*cmd)
	{
		op = is_operand(cmd);
		if (op == -1)
			return (gc_free_item(&d->gc, token), NULL);
		if (op && !is_quoted(*cmd, BUFF_TOK_CMD, SAVE))
			cmd = save_token_op(d, cmd, op, token);
		else if (!op && !ft_strchr(WHITE_SPACE, *cmd))
			cmd = save_token_cmd(d, cmd, token);
		else
			cmd++;
	}
	substitute_var_in_token(d, token);
	if (!is_builtin(token))
		prepend_path(d, &token->cmd);
	return (token);
}

/*
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
*/
