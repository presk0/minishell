/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:49:21 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/02 23:16:50 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*subst_var_and_quotes(char *str)
{
	char	*ret;

	ret = NULL;
	if (str)
	{
		ret = substitute_variables(str);
		ret = rm_quotes(ret);
	}
	return (ret);
}

int	is_to_substitute(char *var)
{
	return (*var == '$' && is_quoted(*var, BUFF_SUBVAR, SAVE) != SIMPLE_QUOTE);
}

char	*substitute_variables(char *input)
{
	char	*result;
	size_t	i_input;
	size_t	i_result;

	result = gc_strdup(&g_d.gc, "");
	i_input = 0;
	i_result = 0;
	is_quoted(0, BUFF_SUBVAR, RESET);
	while (input[i_input] != '\0')
	{
		if (is_to_substitute(input + i_input))
			result = process_dollar(input, &i_input, &i_result, &result);
		else
			append_until_dollar(input, &i_input, &i_result, &result);
	}
	return (result);
}
