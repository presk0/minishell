/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/11 12:09:31 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 12:06:43 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(t_list *gc, char *env[])
{
	t_env	*local_env;

	local_env = gc_malloc(&gc, sizeof(t_env), 1);
	if (!local_env)
		minishell_exit(gc);
	local_env->my_env = cpy_env(gc, env);
	local_env->my_export = init_export(gc, local_env->my_env);
	return (local_env);
}

char	**cpy_env(t_list *gc, char *env[])
{
	char	**my_env;
	int		i;

	i = ft_tablen(env);
	my_env = gc_malloc(&gc, (i + 1) , sizeof(char *));
	my_env[i] = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		my_env[i] = gc_strdup(&gc, env[i]);
		if (!gc_append(&gc, my_env))
			minishell_exit(gc);
		i++;
	}
	return (my_env);
}
