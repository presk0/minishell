/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:09:31 by nkieffer          #+#    #+#             */
/*   Updated: 2024/12/17 18:45:07 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char *env[])
{
	t_env	*local_env;

	local_env = malloc(sizeof(t_env));
	if (env[0] != NULL)
		local_env->my_env = cpy_env(env);
	else
		local_env->my_env = init_null_env();
	local_env->my_export = init_export(local_env->my_env);
	return (local_env);
}

char	**cpy_env(char *env[])
{
	char	**my_env;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	my_env = malloc((i + 1) * sizeof(char *));
	my_env[i] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (my_env);
}

char	**init_null_env(void)
{
	char	**my_env;

	my_env = malloc (4 * sizeof(char *));
	my_env[3] = NULL;
	my_env[0] = ft_strjoin_free2("PWD=", getcwd(NULL, (size_t) NULL));
	my_env[1] = ft_strdup("SHLVL=1");
	my_env[2] = ft_strdup("_=");
	return (my_env);
}
