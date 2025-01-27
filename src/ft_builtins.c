/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 22:27:35 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_cmd_id(t_token *token)
{
	if (ft_strcmp(token->cmd, "echo") == 0)
		token->cmd_id = (int)ECHO_ID;
	else if (ft_strcmp(token->cmd, "cd") == 0)
		token->cmd_id = (int)CD_ID;
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		token->cmd_id = (int)PWD_ID;
	else if (ft_strcmp(token->cmd, "export") == 0)
		token->cmd_id = (int)EXPORT_ID;
	else if (ft_strcmp(token->cmd, "unset") == 0)
		token->cmd_id = (int)UNSET_ID;
	else if (ft_strcmp(token->cmd, "env") == 0)
		token->cmd_id = (int)ENV_ID;
	else if (ft_strcmp(token->cmd, "exit") == 0)
		token->cmd_id = (int)EXIT_ID;
	else
		token->cmd_id = 0;
}

int	exec_builtin(t_token *token)
{
	int	exit_status;

	set_cmd_id(token);
	exit_status = 0;
	if (token->cmd_id == (int)ECHO_ID)
		exit_status = ft_echo(token);
	else if (token->cmd_id == (int)CD_ID)
		exit_status = ft_cd(token);
	else if (token->cmd_id == (int)PWD_ID)
		exit_status = ft_pwd(token);
	else if (token->cmd_id == (int)EXPORT_ID)
		exit_status = ft_export(token);
	else if (token->cmd_id == (int)UNSET_ID)
		exit_status = ft_unset(token);
	else if (token->cmd_id == (int)ENV_ID)
		exit_status = ft_env();
	else if (token->cmd_id == (int)EXIT_ID)
		exit_status = ft_exit();
	return (exit_status);
}

int	exec_builtin_scotch(t_btree *node)
{
	t_btree_content	*c;
	int				ret;

	(void)node;
	c = node->content;
	ret = exec_builtin(&c->token);
	return (ret);
}

int	is_builtin(t_token *token)
{
	if (ft_strcmp(token->cmd, "echo") == 0)
		return (ECHO_ID);
	else if (ft_strcmp(token->cmd, "cd") == 0)
		return (CD_ID);
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		return (PWD_ID);
	else if (ft_strcmp(token->cmd, "export") == 0)
		return (EXPORT_ID);
	else if (ft_strcmp(token->cmd, "unset") == 0)
		return (UNSET_ID);
	else if (ft_strcmp(token->cmd, "env") == 0)
		return (ENV_ID);
	else if (ft_strcmp(token->cmd, "exit") == 0)
		return (EXIT_ID);
	return (0);
}


