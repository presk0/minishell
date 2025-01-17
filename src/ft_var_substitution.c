#include <minishell.h>

char	*substitute_variables(t_list *gc, char *input, char **env)
{
	char	*result;
	//size_t	result_len;
	size_t	i;

	result = gc_malloc(&gc, 1, ft_strlen(input) + 1);
	//result_len = 0;
	i = 0;
	if (!result)
	{
		perror("malloc");
		return (NULL);
	}
	while (input[i] != '\0')
	{
		if (input[i] == '$' && input[i + 1] && !is_quoted(input[i], 0, BUFF_SUBVAR))
			result = process_dollar(gc, input, &i, env, &result);
		else
			i += append_until_dollar(gc, input, i, &result);
	}
	result[i] = '\0';
	return (result);
}

int	strlen_char_quoted(char *cmd, char c)
{
	int	len;

	is_quoted(0, BUFF_STRLEN, RESET);
	len = 0;
	while (*cmd)
	{
		if (!is_quoted(*cmd, BUFF_STRLEN, SAVE))
			if (*cmd == c)
				break ;
		cmd++;
		len++;
	}
	return (len);
}

size_t	append_until_dollar(t_list *gc, char *input, size_t start, char **result)
{
	//size_t	start;
	size_t	next_dollar;
	size_t	chunk_len;

	//start = *i;
	next_dollar = strlen_char_quoted(input + start, '$');
	if (next_dollar > start)
	{
		chunk_len = next_dollar - start;
		gc_str_append(gc, result, input + start);
		//*i += next_dollar;
	}
	return (next_dollar);
}

char	*process_dollar(t_list *gc, char *input, size_t *i, char **env, char **result)
{
	size_t	var_start;
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	var_start = *i + 1;
	var_len = ft_varlen(input + var_start);
	if (var_len > 0)
	{
		var_name = ft_strndup(input + var_start, var_len);
		var_value = ft_getenv(env, var_name);
		free(var_name);
		if (var_value)
		{
			gc_str_append(gc, result, var_value);
		}
		*i += var_len;
	}
	else
	{
		gc_str_append(gc, result, "$");
	}
	(*i)++;
	return (*result);
}

size_t	gc_str_append(t_list *gc, char **result, char *str)
{
	size_t src_len;
	size_t result_len;

	result_len = ft_strlen(*result);
	src_len = ft_strlen(str);
	*result = gc_realloc(gc, *result, result_len, result_len + src_len + 1);
	if (!*result)
	{
		perror("realloc");
		minishell_exit(gc);
	}
	ft_memcpy(*result + result_len, str, src_len);
	return (result_len + src_len);
}
