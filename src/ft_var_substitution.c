/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_var_substitution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/22 11:28:46 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_to_substitute(char *var)
{
	return (*var == '$' && is_quoted(*var, BUFF_SUBVAR, SAVE) != SIMPLE_QUOTE);
}

char	*substitute_variables(char *input)
{
	char	*result;
	size_t	i_input;
	size_t	i_result;

	result = gc_strdup(&d.gc, "");
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

char	*del_char(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i++])
			str[i - 1] = str[i];
	}
	return (str);
}

char	*rm_quotes(char *str)
{
	char	*ret;
	int		last_state;

	ret = str;
	last_state = 0;
	is_quoted(0, BUFF_RMQUOTES, RESET);
	if (str)
	{
		while (*str)
		{
			if (last_state != is_quoted(*str, BUFF_RMQUOTES, SAVE))
			{
				last_state = is_quoted(*str, BUFF_RMQUOTES, READ);
				str = del_char(str);
			}
			else
				str++;
		}
	}
	return (ret);
}

int	strlen_char_simple_quoted(char *cmd, char c, int buff)
{
	int	len;

	//is_quoted(0, buff, RESET);
	len = 0;
	if (!cmd)
		return (0);
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

size_t	append_until_dollar(char *input, size_t *i_input, size_t *i_result, char **result)
{
	size_t	next_dollar;

	next_dollar = strlen_char_simple_quoted(input + *i_input, '$', BUFF_SUBVAR);
	if (next_dollar)
		*i_result = gc_strlcat(&d.gc, result, &input[*i_input], ft_strlen(*result) + next_dollar);
	*i_input += next_dollar;
	return (next_dollar);
}

char	*process_dollar(char *input, size_t *i_input, size_t *i_result, char **result)
{
	size_t	var_start;
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	var_start = *i_input + 1;
	var_len = ft_varlen(input + var_start);
	if (var_len > 0 && input[var_start])
	{
		var_name = ft_strndup(input + var_start, var_len);
		var_value = ft_getenv(var_name);
		if (var_value)
			*i_result += gc_strcat(&d.gc, result, var_value);
		else if (var_name && *var_name)
		{
			*i_result += gc_strcat(&d.gc, result, "$");
			*i_result += gc_strcat(&d.gc, result, var_name);
		}
		free(var_name);
	}
	else
		*i_result = gc_strcat(&d.gc, result, "$");
	*i_input += var_len + 1;
	return (*result);
}
