/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/03 23:34:59 by nidionis         ###   ########.fr       */
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

int	ft_env(t_data *d)
{
	int	i;

	i = 0;
	while (d->env[i] != NULL)
	{
		printf("%s\n", d->env[i]);
		i++;
	}
	return (0);
}

char	*ft_getenv_line(t_data *d, const char *var)
{
	size_t	var_len;
	int		i;

	var_len = ft_strlen(var);
	i = 0;
	while (d->env[i] != NULL)
	{
		if (!ft_strncmp(d->env[i], var, var_len) && d->env[i][var_len] == '=')
			return (d->env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(t_data *d, const char *var)
{
	size_t	var_len;
	int		i;

	var_len = ft_strlen(var);
	i = 0;
	while (d->env[i] != NULL)
	{
		if (!ft_strncmp(d->env[i], var, var_len) && d->env[i][var_len] == '=')
			return (d->env[i] + var_len + 1);
		i++;
	}
	d->status = CLEAN_EXIT;
	return (NULL);
}
