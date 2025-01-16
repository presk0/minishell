/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:26:50 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:24 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_unset(char **local_env, t_token *cmd)
{
	char	**to_unset;
	int		i;

	to_unset = &token->cmd_args[1];
	i = 1;
	while (to_unset[i] != NULL)
	{
		rm_in_export(local_env, to_unset[i]);
		rm_in_env(local_env, to_unset[i]);
		rm_in_vars(local_env, to_unset[i]);
		i++;
	}
	return (0);
}

void	rm_in_export(char **local_env, char *content)
{
	t_export	*to_del;
	t_export	*export;

	export = local_env->my_export;
	if (ft_strcmp_until(&export->line[11], content, '=') == 0)
	{
		to_del = export;
		local_env->my_export = export->next;
		free(to_del);
		return ;
	}
	while (export->next != NULL
		&& ft_strcmp_until(&export->next->line[11], content, '=') != 0)
		export = export->next;
	if (export->next != NULL)
	{
		to_del = export->next;
		export->next = export->next->next;
		free(to_del);
	}
}

void	rm_in_env(char **local_env, char *content)
{
	char	**env;
	int		i;
	char	*to_del;

	env = local_env->my_env;
	i = 0;
	to_del = ft_strjoin(content, "=");
	if (!to_del)
		return ;
	while (env[i] != NULL && ft_strcmp_until(env[i], to_del, '=') != 0)
		i++;
	free(to_del);
	if (env[i] == NULL)
		return ;
	while (env[i + 1] != NULL)
	{
		free(env[i]);
		env[i] = ft_strdup(env[i + 1]);
		if (!env[i])
			return (free_tab(env));
		i++;
	}
	free(env[i]);
	env[i] = NULL;
}

void	rm_in_vars(char **local_env, char *content)
{
	char	**vars;
	int		i;

	vars = local_env->local_vars;
	i = 0;
	if (!vars)
		return ;
	while (vars[i] != NULL && ft_strcmp_until(vars[i], content, '=') != 0)
		i++;
	if (vars[i] == NULL)
		return ;
	while (vars[i + 1] != NULL)
	{
		free(vars[i]);
		vars[i] = ft_strdup(vars[i + 1]);
		if (!vars[i])
			return (free_tab(vars));
		i++;
	}
	free(vars[i]);
	vars[i] = NULL;
}
