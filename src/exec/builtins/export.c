/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlapique <mlapique@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:34:46 by nkieffer          #+#    #+#             */
/*   Updated: 2024/11/20 18:44:10 by mlapique         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	parse_export(char *arg)
{
	int	i;

	i = 0;
	if (ft_isalpha(arg[0]) != 1 && arg[0] != '_')
	{
		ft_print_err("minishell: export: `%s': not a valid identifier\n", arg);
		return (false);
	}
	while (arg[i] != '=' && arg[i] != '\0')
	{
		if (ft_isalnum(arg[i]) != 1 && arg[i] != '_')
		{
			ft_print_err("minishell: export: `%s': not a valid identifier\n", arg);
			return (false);
		}
		i++;
	}
	return (true);
}

int	ft_export(t_env *local_env, char **cmd)
{
	char	**to_export;
	int		i;
	int		ret;

	ret = 0;
	to_export = cmd;
	if (to_export[1] == NULL)
		print_export(local_env);
	i = 1;
	while (to_export[i] != NULL)
	{
		if (parse_export(to_export[i]) == true)
		{
			add_in_export(local_env, to_export[i]);
			if (ft_strchr(to_export[i], '=') != NULL)
			{
				add_in_vars(local_env, to_export[i]);
				add_in_env(local_env, to_export[i]);
			}
		}
		else
			ret = 1;
		i++;
	}
	return (ret);
}

void	add_in_export(t_env *local_env, char *content)
{
	t_export	*new_node;
	t_export	*export;

	new_node = export_new_node(content);
	export = local_env->my_export;
	if (ft_strcmp_until(export->line, new_node->line, '=') > 0)
	{
		new_node->next = export;
		local_env->my_export = new_node;
		return ;
	}
	while (export->next != NULL
		&& ft_strcmp_until(export->next->line, new_node->line, '=') < 0)
		export = export->next;
	if (export->next != NULL
		&& ft_strcmp_until(export->next->line, new_node->line, '=') == 0)
		return (replace_in_export(export, new_node));
	new_node->next = export->next;
	export->next = new_node;
}

void	replace_in_export(t_export *export, t_export *new_node)
{
	if (ft_strchr(new_node->line, '=') != NULL)
	{
		new_node->next = export->next->next;
		free_export_node(export->next);
		export->next = new_node;
	}
}