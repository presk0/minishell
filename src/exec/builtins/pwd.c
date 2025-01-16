/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 12:18:33 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:24 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(char **local_env)
{
	char	*path;

	path = ft_getenv(local_env, "PWD");
	if (!path)
		return (1);
	printf("%s\n", path);
	return (0);
}
