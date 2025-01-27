/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 14:15:38 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	ft_setenv(char *var)
//{
//	char	*delimiter;
//
//	if (var != NULL)
//	{
//		delimiter = ft_strchr(var, '=');
//		if (!delimiter)
//			return (FALSE);
//		if (ft_varlen(var))
//		{
//			if (is_var_in_env(var))
//				unset_var_in_env(var);
//			append_tab(&d.env, var);
//		}
//	}
//	return (TRUE);
//}
//
// int	ft_export(t_token *token)
//{
//	int	i;
//
//	if (!token->args[1])
//	{
//		print_export(d.env);
//		return (0);
//	}
//	i = 1;
//	while (token->args[i] != NULL)
//	{
//		if (!ft_setenv(token->args[i]))
//			continue ;
//	}
//	return (0);
//}
//
// int	ft_env(void)
//{
//	for (int i = 0; d.env[i] != NULL; i++)
//	{
//		printf("%s\n", d.env[i]);
//	}
//	return (0);
//}
//
