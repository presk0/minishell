/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:04:07 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:24 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
/*

static void	set_cmd_id(t_token *token)
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

int	exec_builtin(t_list *gc, t_token *token, char ***env_in)
{
	int	exit_status;
	t_env	*env;

	// if (apply_redirections(token, i))
	// 	ft_print_err("%s: %d: err applying redir\n", __FILE__, __LINE__);
	set_cmd_id(token);
	env = *env_in;
	exit_status = 0;
	if (token->cmd_id == (int)ECHO_ID)
		exit_status = ft_echo(token->args);
	else if (token->cmd_id == (int)CD_ID)
		exit_status = ft_cd(env, token->args);
	else if (token->cmd_id == (int)PWD_ID)
		exit_status = ft_pwd(env);
	else if (token->cmd_id == (int)EXPORT_ID)
		exit_status = ft_export(env, token->args);
	else if (token->cmd_id == (int)UNSET_ID)
		exit_status = ft_unset(env, token);
	else if (token->cmd_id == (int)ENV_ID)
		exit_status = ft_env(env);
	else if (token->cmd_id == (int)EXIT_ID)
		exit_status = ft_exit(gc, token);
	// if (restore_std_fds(m->std_fds) == -1)
	// 	ft_print_err("%s: %d: err restore std fds", __FILE__, __LINE__);
	return (exit_status);
}
*/
