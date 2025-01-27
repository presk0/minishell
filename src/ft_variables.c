/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_variables.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 14:04:21 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	var_len(char *var)
{
	size_t	len;

	len = 0;
	if (var[len] && ft_isalnum(var[len]))
		len++;
	while (var[len] && (ft_isalnum(var[len]) || var[len] == '_'))
		len++;
	return (len);
}

int	ft_varlen(const char *var)
{
	int	len;

	if (!var || !isalpha(var[0]))
		return (0);
	len = 1;
	while (var[len] != '\0')
	{
		if (!isalnum(var[len]) || var[len] == '_')
			break ;
		len++;
	}
	return (len);
}

int	is_valid_var_name(const char *var)
{
	int	i;

	i = 1;
	if (!var || !isalpha(var[0]))
		return (FALSE);
	while (var[i] != '\0')
	{
		if (!isalnum(var[i]) && var[i] != '_')
			return (FALSE);
		if (var[i] == '=')
			break ;
		i++;
	}
	return (TRUE);
}

int	is_var_in_env(const char *var)
{
	size_t	var_len;
	int		i;

	i = 0;
	var_len = strlen(var);
	while (d.env[i] != NULL)
	{
		if (strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
