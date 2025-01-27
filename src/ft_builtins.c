#include <minishell.h>


// Comparison function for qsort

int compare_strings(const void *a, const void *b) {

    return strcmp(*(const char **)a, *(const char **)b);

}







// Function to perform bubble sort on an array of strings

void ft_easy_sort(char **tab) {

    if (tab == NULL) {

        return; // Return if the input tab is NULL

    }


    size_t len = 0;

    // Calculate the length of the tab

    while (tab[len] != NULL) {

        len++;

    }


    // Bubble sort algorithm

    for (size_t i = 0; i < len - 1; i++) {

        for (size_t j = 0; j < len - 1 - i; j++) {

            // Compare adjacent strings

            if (strcmp(tab[j], tab[j + 1]) > 0) {

                // Swap if they are in the wrong order

                char *temp = tab[j];

                tab[j] = tab[j + 1];

                tab[j + 1] = temp;

            }

        }

    }

}











char **sort_char_tab(char **tab) {

    if (tab == NULL) {

        return NULL; // Return NULL if the input tab is NULL

    }


    size_t len = 0;

    while (tab[len] != NULL) {

        len++; // Calculate the length of the tab

    }


    // Sort the tab using qsort

    qsort(tab, len, sizeof(char *), compare_strings);


    return tab; // Return the sorted tab

}








char	*shift_char(char *str, size_t shift_len)
{
	int	i;

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

	var_len = strlen(var);
	for (int i = 0; d.env[i] != NULL; i++)
	{
		if (strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
		{
			return (d.env[i]);
		}
	}
	return (NULL);
}

char	*ft_getenv(const char *var)
{
	size_t	var_len;

	var_len = strlen(var);
	for (int i = 0; d.env[i] != NULL; i++)
	{
		if (strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
		{
			return (d.env[i] + var_len + 1);
		}
	}
	return (NULL);
}

int	ft_exit()
{
	d.status = SUCCESS;
	minishell_exit(NULL, 0);
	return (0);
}

int	unset_var_in_env(char *var)
{
	int		i;
	int		j;
	size_t	var_len;

	if (!d.env || !var)
		return (FAILURE);
	var_len = strlen(var);
	i = 0;
	while (d.env[i] != NULL)
	{
		if (ft_strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
		{
			gc_free_item(&d.gc, d.env[i]);
			j = i;
			while (d.env[j] != NULL)
			{
				d.env[j] = d.env[j + 1];
				j++;
			}
			d.env[j] = NULL;
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
			var = gc_strndup(&d.gc, var_line, var_len);
			unset_var_in_env(var);
			gc_free_item(&d.gc, var);
			append_tab(&d.env, gc_strdup(&d.gc, var_line));
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
		print_export(d.env);
		return (0);
	}
	i = 1;
	while (token->args[i] != NULL)
	{
		if (ft_setenv(token->args[i++]) == SUCCESS)
			continue ;
	}
	return (0);
}

int	ft_env()
{
	for (int i = 0; d.env[i] != NULL; i++)
	{
		printf("%s\n", d.env[i]);
	}
	return (0);
}

int ft_cd(t_token *token)
{
    char *target_dir;
    char *newpwd;
    char *oldpwd;

	newpwd = NULL;
	oldpwd = gc_strdup(&d.gc, "OLDPWD=");
	gc_strcat(&d.gc, &oldpwd, ft_getenv("PWD"));
    if (token->args[1] != NULL)
        target_dir = token->args[1];
    else
    {
        target_dir = ft_getenv("HOME");
        if (target_dir == NULL)
        {
            fprintf(stderr, "cd: HOME not set\n");
            return 1;
        }
    }
   	if (access(target_dir, F_OK) != SUCCESS)
	{
		gc_free_item(&d.gc, newpwd);
		d.status = 1;
		return (FAILURE);
	}
	else
	{
		if (chdir(target_dir) != SUCCESS)
		{
			perror("cd failed");
			gc_free_item(&d.gc, oldpwd);
			return FAILURE;
		}
		char	cwd[1024];
		newpwd = gc_strdup(&d.gc, "PWD=");
		getcwd(cwd, sizeof(cwd));
		gc_strcat(&d.gc, &newpwd, cwd);
		ft_setenv(oldpwd);
		ft_setenv(newpwd);
		d.status = 0;
    }
    return 0;
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
