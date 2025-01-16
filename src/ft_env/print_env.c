/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/11 13:49:31 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 12:15:26 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_list *gc, t_env *local_env)
{
	int	i;

	(void)gc;
	i = 0;
	while (local_env->my_env[i] != NULL)
	{
		printf("%s\n", local_env->my_env[i]);
		i++;
	}
}

void	print_export(t_list *gc, t_env *local_env)
{
	t_export	*export;

	(void)gc;
	export = local_env->my_export;
	while (export != NULL)
	{
		printf("%s\n", export->line);
		export = export->next;
	}
}
