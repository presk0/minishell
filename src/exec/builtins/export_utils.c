/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:53:43 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:24 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	add_in_vars(char **local_env, char *content)
{
	char	**vars;
	char	**new_vars;
	int		i;

	vars = local_env->local_vars;
	i = 0;
	while (vars != NULL && vars[i] != NULL)
		i++;
	new_vars = ft_calloc((i + 2), sizeof(char *));
	if (!new_vars)
		return ;
	new_vars[i + 1] = NULL;
	i = 0;
	while (vars != NULL && vars[i] != NULL)
	{
		new_vars[i] = ft_strdup(vars[i]);
		if (!new_vars)
			return (free_tab(new_vars));
		i++;
	}
	new_vars[i] = ft_strdup(content);
	if (!new_vars)
		return (free_tab(new_vars));
	if (local_env->local_vars != NULL)
		free_split(local_env->local_vars);
	local_env->local_vars = new_vars;
}

void	replace_in_vars(char **local_env, char *content)
{
	char	**vars;
	int		i;

	vars = local_env->local_vars;
	i = 0;
	while (ft_strcmp_until(vars[i], content, '='))
		i++;
	free(vars[i]);
	vars[i] = ft_strdup(content);
	if (!vars[i])
		free_tab(vars);
}
