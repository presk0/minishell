/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/11 13:20:26 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 12:01:15 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_list *gc, t_env *local_env)
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
	free_export(gc, local_env->my_export);
	free(local_env);
}

void	free_export(t_list *gc, t_export *first)
{
	t_export	*to_free;
	t_export	*next;

	to_free = first;
	while (to_free != NULL)
	{
		next = to_free->next;
		free_export_node(gc, to_free);
		to_free = next;
	}
}

void	free_export_node(t_list *gc, t_export *to_free)
{
	gc_free_item(&gc, to_free->line);
	gc_free_item(&gc, to_free);
}
