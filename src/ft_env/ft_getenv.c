/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/11 12:11:52 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 12:02:10 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list *gc, char	**local_env, char *to_find)
{
	// char	**local_env;
	int		to_find_len;
	int		i;

	(void)gc;
	// local_env = env->my_env;
	to_find_len = ft_strlen(to_find);
	i = 0;
	while (local_env[i] != NULL)
	{
		if (ft_strncmp(local_env[i], to_find, to_find_len) == 0
			&& local_env[i][to_find_len] == '=')
			return (&local_env[i][to_find_len + 1]);
		i++;
	}
	return (NULL);
}
