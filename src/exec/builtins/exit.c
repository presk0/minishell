/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:25:07 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 15:43:46 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	ft_is_long(char *cmd, bool negatif)
{
	if (negatif == true)
	{
		if (ft_strcmp(&cmd[1], "9223372036854775808") <= 0)
			return (true);
		return (false);
	}
	else
	{
		if (ft_strcmp(cmd, "9223372036854775807") <= 0)
			return (true);
		return (false);
	}
	return (false);
}

bool	is_error(char **cmd)
{
	bool	negatif;

	negatif = false;
	if (cmd[1][0] == '-')
		negatif = true;
	if (ft_isnumber(cmd[1]) == 1)
		if (ft_is_long(cmd[1], negatif) == true)
			return (false);
	return (ft_print_err("minishell: exit: %s: numeric argument required\n", cmd[1]), true);
}

int	ft_exit(t_list *gc, t_token *cmd)
{
	if (cmd->cmd_args[1])
	{
		if (cmd->cmd_args[2])
			return (ft_print_err("minishell: exit: too many arguments\n"), m->exit = 1, 0);
		if (cmd->cmd_args[1][0] == '-')
			if (cmd->cmd_args[1][1] == '-')
				if (cmd->cmd_args[1][2] == '\0')
					return (0);
		if (is_error(cmd->cmd_args) == true)
			return (m->exit = 2, 0);
	}
	minishell_exit(gc);
}
