/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 23:59:57 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_var_index(char **env, char *var, size_t var_len)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	ft_env(void)
{
	int	i;

	i = 0;
	while (g_d.env[i] != NULL)
	{
		printf("%s\n", g_d.env[i]);
		i++;
	}
	return (0);
}

char	*ft_getenv_line(const char *var)
{
	size_t	var_len;
	int		i;

	var_len = ft_strlen(var);
	i = 0;
	while (g_d.env[i] != NULL)
	{
		if (!ft_strncmp(g_d.env[i], var, var_len) && g_d.env[i][var_len] == '=')
			return (g_d.env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(const char *var)
{
	size_t	var_len;
	int		i;

	var_len = ft_strlen(var);
	i = 0;
	while (g_d.env[i] != NULL)
	{
		if (!ft_strncmp(g_d.env[i], var, var_len) && g_d.env[i][var_len] == '=')
			return (g_d.env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}