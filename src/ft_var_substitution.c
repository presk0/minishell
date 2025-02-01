/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/02/01 19:55:41 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	append_until_dollar(char *input, size_t *i_input, size_t *i_result,
		char **result)
{
	size_t	next_dollar;

	next_dollar = strlen_char_simple_quoted(input + *i_input, '$', BUFF_SUBVAR);
	if (next_dollar)
		*i_result = gc_strlcat(&g_d.gc, result, &input[*i_input],
				ft_strlen(*result) + next_dollar);
	*i_input += next_dollar;
	return (next_dollar);
}

char	*handle_variable_expansion(char **result, \
								char *var_name, size_t *i_result)
{
	char	*var_value;

	var_value = ft_getenv(var_name);
	if (var_value)
		*i_result += gc_strcat(&g_d.gc, result, var_value);
	else if (var_name && *var_name)
	{
		*i_result += gc_strcat(&g_d.gc, result, "$");
		*i_result += gc_strcat(&g_d.gc, result, var_name);
	}
	return (var_value);
}

char	*process_dollar(char *in, size_t *i_in, size_t *i_result, char **result)
{
	char	*var_name;
	size_t	var_start;
	size_t	var_len;

	var_start = *i_in + 1;
	var_len = ft_varlen(in + var_start);
	if (var_len > 0 && in[var_start])
	{
		var_name = ft_strndup(in + var_start, var_len);
		if (var_name)
		{
			handle_variable_expansion(result, var_name, i_result);
			free(var_name);
		}
	}
	else if (var_len == 0 && in[var_start] == '?')
	{
		*i_result = gc_strcat(&g_d.gc, result, \
						gc_append(&g_d.gc, ft_itoa(g_d.status)));
		var_len = 1;
	}
	else
		*i_result = gc_strcat(&g_d.gc, result, "$");
	*i_in += var_len + 1;
	return (*result);
}
