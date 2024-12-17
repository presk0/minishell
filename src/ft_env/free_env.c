/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:20:26 by nkieffer          #+#    #+#             */
/*   Updated: 2024/12/17 18:43:36 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *local_env)
{
	char	**env;
	int		i;

	env = local_env->my_env;
	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
	free_export(local_env->my_export);
	free(local_env);
}

void	free_export(t_export *first)
{
	t_export	*to_free;
	t_export	*next;

	to_free = first;
	while (to_free != NULL)
	{
		next = to_free->next;
		free_export_node(to_free);
		to_free = next;
	}
}

void	free_export_node(t_export *to_free)
{
	free(to_free->line);
	free(to_free);
}
