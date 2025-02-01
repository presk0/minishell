/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/02/01 18:55:59 by nidionis         ###   ########.fr       */
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

//char	*process_dollar(char *input, size_t *i_input, size_t *i_result,
//		char **result)
//{
//	size_t	var_start;
//	size_t	var_len;
//	char	*var_name;
//	char	*var_value;
//
//	var_start = *i_input + 1;
//	var_len = ft_varlen(input + var_start);
//	if (var_len > 0 && input[var_start])
//	{
//		var_name = ft_strndup(input + var_start, var_len);
//		var_value = ft_getenv(var_name);
//		if (var_value)
//			*i_result += gc_strcat(&g_d.gc, result, var_value);
//		else if (var_name && *var_name)
//		{
//			*i_result += gc_strcat(&g_d.gc, result, "$");
//			*i_result += gc_strcat(&g_d.gc, result, var_name);
//		}
//		free(var_name);
//	}
//	else
//		*i_result = gc_strcat(&g_d.gc, result, "$");
//	*i_input += var_len + 1;
//	return (*result);
//}

char	*handle_variable_expansion(char **result, char *var_name, size_t *i_result)
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

void	process_valid_variable(char *input, size_t var_start, size_t var_len,
		char **result, size_t *i_result)
{
	char	*var_name;

	var_name = ft_strndup(input + var_start, var_len);
	if (var_name)
	{
		handle_variable_expansion(result, var_name, i_result);
		free(var_name);
	}
}

char	*process_dollar(char *input, size_t *i_input, size_t *i_result,
		char **result)
{
	size_t	var_start;
	size_t	var_len;

	var_start = *i_input + 1;
	var_len = ft_varlen(input + var_start);
	if (var_len > 0 && input[var_start])
		process_valid_variable(input, var_start, var_len, result, i_result);
	else if (var_len == 0 && input[var_start] == '?')
	{
		*i_result = gc_strcat(&g_d.gc, result, gc_append(&g_d.gc, ft_itoa(g_d.status)));
		var_len = 1;
	}
	else
		*i_result = gc_strcat(&g_d.gc, result, "$");
	*i_input += var_len + 1;
	return (*result);
}
