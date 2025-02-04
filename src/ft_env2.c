/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:01:21 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_var_from_env(t_data *d, char **env, int index)
{
	gc_free_item(&d->gc, env[index]);
	env[index] = env[index + 1];
	index++;
	while (env[index] != NULL)
	{
		env[index] = env[index + 1];
		index++;
	}
	env[index] = NULL;
}

int	unset_var_in_env(t_data *d, char *var)
{
	int		var_index;
	size_t	var_len;

	if (!d->env || !var)
		return (FAILURE);
	var_len = ft_strlen(var);
	var_index = find_var_index(d->env, var, var_len);
	if (var_index == -1)
		return (FAILURE);
	remove_var_from_env(d, d->env, var_index);
	return (SUCCESS);
}

int	ft_unset(t_data *d, t_token *token)
{
	char	*var;

	var = token->args[1];
	return (unset_var_in_env(d, var));
}

int	ft_setenv(t_data *d, char *var_line)
{
	char	*delimiter;
	size_t	var_len;
	char	*var;

	if (var_line != NULL)
	{
		delimiter = ft_strchr(var_line, '=');
		if (!delimiter)
			return (FAILURE);
		var_len = ft_varlen(var_line);
		if (var_len)
		{
			var = gc_strndup(&d->gc, var_line, var_len);
			unset_var_in_env(d, var);
			gc_free_item(&d->gc, var);
			append_tab(&d->env, gc_strdup(&d->gc, var_line));
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}
