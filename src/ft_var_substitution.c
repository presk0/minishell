/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/22 07:20:22 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_to_substitute(char *var)
{
	return (*var == '$' && *(var + 1) && is_quoted(*var, BUFF_SUBVAR, SAVE) != SIMPLE_QUOTE);
}

char	*substitute_variables(char *input)
{
	char	*result;
	size_t	i_input;
	size_t	i_result;

	result = NULL;
	i_input = 0;
	i_result = 0;
	is_quoted(0, BUFF_SUBVAR, RESET);
	while (input[i_input] != '\0')
	{
		//if (is_to_substitute(input + i_input))
		//	result = process_dollar(input, &i_input, &i_result, &result);
		//else
		//	append_until_dollar(input, &i_input, &result);
	}
	return (result);
}

int	strlen_char_simple_quoted(char *cmd, char c, int buff)
{
	int	len;

	//is_quoted(0, buff, RESET);
	len = 0;
	while (*cmd)
	{
		if (is_quoted(*cmd, buff, SAVE) != SIMPLE_QUOTE)
			if (*cmd == c)
				break ;
		cmd++;
		len++;
	}
	return (len);
}


size_t	append_until_dollar(char *input, size_t *start, char **result)
{
	size_t	next_dollar;
	size_t	chunk_len;

	next_dollar = strlen_char_simple_quoted(input + *start, '$', BUFF_SUBVAR);
	if (next_dollar > *start)
	{
		chunk_len = next_dollar - *start;
		gc_strcat(&d.gc, result, input + *start);
	}
	*start += next_dollar;
	return (next_dollar);
}

char	*process_dollar(char *input, size_t *i, char **result)
{
	size_t	var_start;
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	var_start = *i + 1;
	var_len = ft_varlen(input + var_start);
	if (var_len > 0 && input[var_start])
	{
		var_name = ft_strndup(input + var_start, var_len);
		var_value = ft_getenv(var_name);
		if (var_value)
			gc_strcat(&d.gc, result, var_value);
		else if (var_name && *var_name)
		{
			gc_strcat(&d.gc, result, "$");
			gc_strcat(&d.gc, result, var_name);
		}
		*i += var_len;
		free(var_name);
	}
	else
		gc_strcat(&d.gc, result, "$");
	*i += var_len;
	return (*result);
}
