/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaume <lmaume@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:31:19 by nkieffer          #+#    #+#             */
/*   Updated: 2024/11/20 18:30:07 by lmaume           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(t_env *local_env)
{
	print_env(local_env);
	return (0);
}

void	add_in_env(t_env *local_env, char *content)
{
	char	**env;
	char	**new_env;
	int		i;

	env = local_env->my_env;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strcmp_until(env[i], content, '=') == 0)
			return (replace_in_env(local_env, content));
		i++;
	}
	new_env = ft_calloc((i + 2), sizeof(char *));
	if (!new_env)
		return ;
	new_env[i + 1] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
			return (free_split(local_env->my_env), free_tab(new_env));
		i++;
	}
	new_env[i] = ft_strdup(content);
	if (!new_env)
		return (free_split(local_env->my_env), free_tab(new_env));
	free_split(local_env->my_env);
	local_env->my_env = new_env;
}

void	replace_in_env(t_env *local_env, char *content)
{
	char	**env;
	int		i;

	env = local_env->my_env;
	i = 0;
	while (ft_strcmp_until(env[i], content, '='))
		i++;
	free(env[i]);
	env[i] = ft_strdup(content);
	if (!env[i])
		free_tab(env);
}
