#include <minishell.h>

// Comparison function for qsort
int	compare_strings(const void *a, const void *b)
{
	return (strcmp(*(const char **)a, *(const char **)b));
}

// Function to perform bubble sort on an array of strings
void	ft_easy_sort(char **tab)
{
	size_t	len;
	size_t	i;
	size_t	j;
	char	*temp;

	if (tab == NULL)
		return ;
	len = 0;
	while (tab[len] != NULL)
		len++;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (strcmp(tab[j], tab[j + 1]) > 0)
			{
				temp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

int	ft_env(void)
{
	int	i;

	i = 0;
	while (g_d.env[i] != NULL)
	{
		printf("%s\n", g_d.env[i]);
		i++;
	}
	return (0);
}

char	**sort_char_tab(char **tab)
{
	size_t	len;

	if (tab == NULL)
		return (NULL);
	len = 0;
	while (tab[len] != NULL)
		len++;
	qsort(tab, len, sizeof(char *), compare_strings);
	return (tab);
}

char	*shift_char(char *str, size_t shift_len)
{
	size_t	i;

	if (ft_strlen(str) < shift_len)
		return (NULL);
	i = shift_len;
	if (str)
	{
		while (str[i])
		{
			str[i - shift_len] = str[i];
			i++;
		}
	}
	return (str);
}

char	*shift_left(char *str, size_t shift_len)
{
	char	*ret;

	ret = str;
	if (str)
		while (*str)
			str = shift_char(str, shift_len);
	return (ret);
}

void	print_export(char **tab)
{
	char	**t;
	size_t	i;

	t = ft_duplicate_tab(tab);
	ft_easy_sort(t);
	i = 0;
	while (t[i])
		printf("declare -x %s\n", t[i++]);
	ft_free_split(&t);
}

char	*ft_getenv_line(const char *var)
{
	size_t	var_len;
	int		i;

	var_len = strlen(var);
	i = 0;
	while (g_d.env[i] != NULL)
	{
		if (strncmp(g_d.env[i], var, var_len) == 0 && g_d.env[i][var_len] == '=')
			return (g_d.env[i]);
		i++;
	}
	return (NULL);
}

char	*ft_getenv(const char *var)
{
	size_t	var_len;
	int		i;

	var_len = strlen(var);
	i = 0;
	while (g_d.env[i] != NULL)
	{
		if (strncmp(g_d.env[i], var, var_len) == 0 && g_d.env[i][var_len] == '=')
			return (g_d.env[i] + var_len + 1);
		i++;
	}
	return (NULL);
}

int	ft_exit(void)
{
	g_d.status = SUCCESS;
	minishell_exit(NULL, 0);
	return (0);
}

int	unset_var_in_env(char *var)
{
	int		i;
	int		j;
	size_t	var_len;

	if (!g_d.env || !var)
		return (FAILURE);
	var_len = strlen(var);
	i = 0;
	while (g_d.env[i] != NULL)
	{
		if (ft_strncmp(g_d.env[i], var, var_len) == 0 && g_d.env[i][var_len] == '=')
		{
			gc_free_item(&g_d.gc, g_d.env[i]);
			j = i;
			while (g_d.env[j] != NULL)
			{
				g_d.env[j] = g_d.env[j + 1];
				j++;
			}
			g_d.env[j] = NULL;
			return (SUCCESS);
		}
		i++;
	}
	return (FAILURE);
}

int	ft_unset(t_token *token)
{
	char	*var;

	var = token->args[1];
	return (unset_var_in_env(var));
}

int	ft_setenv(char *var_line)
{
	char	*delimiter;
	size_t	var_len;
	char	*var;

	if (var_line != NULL)
	{
		delimiter = ft_strchr(var_line, '=');
		if (!delimiter)
			return (FAILURE);
		var_len = ft_varlen(var_line);
		if (var_len)
		{
			var = gc_strndup(&g_d.gc, var_line, var_len);
			unset_var_in_env(var);
			gc_free_item(&g_d.gc, var);
			append_tab(&g_d.env, gc_strdup(&g_d.gc, var_line));
		}
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

int	ft_export(t_token *token)
{
	int	i;

	if (!token->args[1])
	{
		print_export(g_d.env);
		return (0);
	}
	i = 1;
	while (token->args[i] != NULL)
	{
		if (ft_setenv(token->args[i]) == SUCCESS)
			i++;
	}
	return (0);
}

int	ft_cd(t_token *token)
{
	char	*target_dir;
	char	*newpwd;
	char	*oldpwd;
	char	cwd[1024];

	newpwd = NULL;
	oldpwd = gc_strdup(&g_d.gc, "OLDPWD=");
	gc_strcat(&g_d.gc, &oldpwd, ft_getenv("PWD"));
	if (token->args[1] != NULL)
		target_dir = token->args[1];
	else
	{
		target_dir = ft_getenv("HOME");
		if (target_dir == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	if (access(target_dir, F_OK) != SUCCESS)
	{
		gc_free_item(&g_d.gc, newpwd);
		g_d.status = 1;
		return (FAILURE);
	}
	else
	{
		if (chdir(target_dir) != SUCCESS)
		{
			perror("cd failed");
			gc_free_item(&g_d.gc, oldpwd);
			return (FAILURE);
		}
		newpwd = gc_strdup(&g_d.gc, "PWD=");
		getcwd(cwd, sizeof(cwd));
		gc_strcat(&g_d.gc, &newpwd, cwd);
		ft_setenv(oldpwd);
		ft_setenv(newpwd);
		g_d.status = 0;
	}
	return (0);
}

int	ft_echo(t_token *token)
{
	int	newline;
	int	i;

	newline = TRUE;
	i = 1;
	if (token->args[1] != NULL && strcmp(token->args[1], "-n") == 0)
	{
		newline = FALSE;
		i++;
	}
	while (token->args[i] != NULL)
	{
		write(STDOUT_FILENO, token->args[i], strlen(token->args[i]));
		if (token->args[i + 1] != NULL)
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
