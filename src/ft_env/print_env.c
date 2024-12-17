/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:49:31 by nkieffer          #+#    #+#             */
/*   Updated: 2024/09/18 14:44:28 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_env *local_env)
{
	int	i;

	i = 0;
	while (local_env->my_env[i] != NULL)
	{
		printf("%s\n", local_env->my_env[i]);
		i++;
	}
}

void	print_export(t_env *local_env)
{
	t_export	*export;

	export = local_env->my_export;
	while (export != NULL)
	{
		printf("%s\n", export->line);
		export = export->next;
	}
}
