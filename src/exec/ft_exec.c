/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 19:04:07 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 14:42:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	set_cmd_id(t_token *token)
{
	if (ft_strcmp(token->cmd, "echo") == 0)
		token->cmd_id = ECHO_ID;
	else if (ft_strcmp(token->cmd, "cd") == 0)
		token->cmd_id = CD_ID;
	else if (ft_strcmp(token->cmd, "pwd") == 0)
		token->cmd_id = PWD_ID;
	else if (ft_strcmp(token->cmd, "export") == 0)
		token->cmd_id = EXPORT_ID;
	else if (ft_strcmp(token->cmd, "unset") == 0)
		token->cmd_id = UNSET_ID;
	else if (ft_strcmp(token->cmd, "env") == 0)
		token->cmd_id = ENV_ID;
	else if (ft_strcmp(token->cmd, "exit") == 0)
		token->cmd_id = EXIT_ID;
	else
		token->cmd_id = 0;
}

int	exec_builtin(t_token *c)
{
	int	exit_status;

	// if (apply_redirections(c, i))
	// 	ft_print_err("%s: %d: err applying redir\n", __FILE__, __LINE__);
	exit_status = 0;
	if (c->cmd_id == ECHO_ID)
		exit_status = ft_echo(c->args);
	else if (c->cmd_id == CD_ID)
		exit_status = ft_cd(m->env, c->args);
	else if (c->cmd_id == PWD_ID)
		exit_status = ft_pwd(m->env);
	else if (c->cmd_id == EXPORT_ID)
		exit_status = ft_export(m->env, c->args);
	else if (c->cmd_id == UNSET_ID)
		exit_status = ft_unset(m->env, c);
	else if (c->cmd_id == ENV_ID)
		exit_status = ft_env(m->env);
	else if (c->cmd_id == EXIT_ID)
		exit_status = ft_exit(m, c);
	// if (restore_std_fds(m->std_fds) == -1)
	// 	ft_print_err("%s: %d: err restore std fds", __FILE__, __LINE__);
	return (exit_status);
}
