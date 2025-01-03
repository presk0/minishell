/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:18:33 by nkieffer          #+#    #+#             */
/*   Updated: 2024/11/07 15:29:56 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_env *local_env)
{
	char	*path;

	path = ft_getenv(local_env, "PWD");
	if (!path)
		return (1);
	printf("%s\n", path);
	return (0);
}
