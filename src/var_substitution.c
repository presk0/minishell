/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_substitution.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 19:49:21 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:55:29 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*subst_var_and_quotes(t_data *d, char *str)
{
	char	*ret;

	ret = NULL;
	if (str)
	{
		ret = substitute_variables(d, str);
		ret = rm_quotes(ret);
	}
	return (ret);
}

int	is_to_substitute(char *var)
{
	return (*var == '$' && is_quoted(*var, BUFF_SUBVAR, SAVE) != SIMPLE_QUOTE);
}

char	*substitute_variables(t_data *d, char *input)
{
	t_norminette_sucks	v;

	v.input = input;
	v.result = gc_strdup(&d->gc, "");
	v.i_input = 0;
	v.i_result = 0;
	is_quoted(0, BUFF_SUBVAR, RESET);
	while (v.input[v.i_input] != '\0')
	{
		if (is_to_substitute(v.input + v.i_input))
			v.result = process_dollar(d, &v);
		else
			append_until_dollar(d, &v);
	}
	return (v.result);
}
