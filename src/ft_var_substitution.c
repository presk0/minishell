/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/02/04 00:49:17 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	append_until_dollar(t_data *d, t_norminette_sucks *v)
{
	size_t	next_dollar;

	next_dollar = strlen_char_simple_quoted(v->input + v->i_input, '$', BUFF_SUBVAR);
	if (next_dollar)
		v->i_result = gc_strlcat(&d->gc, &v->result, &v->input[v->i_input],
				ft_strlen(v->result) + next_dollar);
	v->i_input += next_dollar;
	return (next_dollar);
}

char	*handle_variable_expansion(t_data *d, char **result, \
								char *var_name, size_t *i_result)
{
	char	*var_value;

	var_value = ft_getenv(d, var_name);
	if (var_value)
		*i_result += gc_strcat(&d->gc, result, var_value);
	else if (var_name && *var_name)
	{
		*i_result += gc_strcat(&d->gc, result, "$");
		*i_result += gc_strcat(&d->gc, result, var_name);
	}
	return (var_value);
}

char	*process_dollar(t_data *d, t_norminette_sucks *v)
{
	char	*var_name;
	size_t	var_start;
	size_t	var_len;

	var_start = v->i_input + 1;
	var_len = ft_varlen(v->input + var_start);
	if (var_len > 0 && v->input[var_start])
	{
		var_name = ft_strndup(v->input + var_start, var_len);
		if (var_name)
		{
			handle_variable_expansion(d, &v->result, var_name, &v->i_result);
			free(var_name);
		}
	}
	else if (var_len == 0 && v->input[var_start] == '?')
	{
		v->i_result = gc_strcat(&d->gc, &v->result, \
						gc_append(&d->gc, ft_itoa(d->status)));
		var_len = 1;
	}
	else
		v->i_result = gc_strcat(&d->gc, &v->result, "$");
	v->i_input += var_len + 1;
	return (v->result);
}
