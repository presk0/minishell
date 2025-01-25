#include <minishell.h>

void	print_export(char **tab)
{
	while (*tab)
	{
		printf("declare -x%s\n", *tab++);
	}
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
	minishell_exit("exit\n", 0);
	return (0);
}

int	unset_var_in_env(char *var)
{
	int		i;
	int		j;
	size_t	var_len;

	var_len = strlen(var);
	i = 0;
	while (d.env[i] != NULL)
	{
		if (ft_strncmp(d.env[i], var, var_len) == 0 && d.env[i][var_len] == '=')
		{
			gc_free_item(&d.gc, d.env[i]);
			j = 0;
			while (d.env[j] != NULL)
			{
				d.env[j] = d.env[j + 1];
				j++;
			}
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(t_token *token)
{
	char	*var;

	var = token->args[1];
	return (unset_var_in_env(var));
}




int	ft_setenv(char *var)
{
	char	*delimiter;

	if (var != NULL)
	{
		delimiter = ft_strchr(var, '=');
		if (!delimiter)
			return (FALSE);
		if (ft_varlen(var))
		{
			if (is_var_in_env(var))
				unset_var_in_env(var);
			append_tab(&d.env, var);
		}
	}
	return (TRUE);
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
		if (!ft_setenv(token->args[i]))
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


int	ft_cd(t_token *token)
{
	char	*path;
	char	cwd[1024];
	char	*env_line;

	if (token->args[1] == NULL)
	{
		path = ft_getenv("HOME");
		if (path == NULL)
		{
			fprintf(stderr, "minishell: cd: HOME not set\n");
			return (1);
		}
	}
	else
		path = token->args[1];
	if (chdir(path) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		env_line = gc_strjoin("PWD=", cwd);
		printf("%s\n", env_line);
		if (!ft_setenv(env_line))
		{
			fprintf(stderr, "minishell: cd: failed to update PWD\n");
			return (1);
		}
	}
	else
	{
		perror("minishell: cd: failed to get current directory");
		return (1);
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
	{
		write(STDOUT_FILENO, "\n", 1);
	}
	return (0);
}