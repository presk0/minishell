#include <minishell.h>

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
	while (*tab)
	{
		printf("declare -x%s\n", *tab++);
	}
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
	minishell_exit("exit\n", 255);
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
			return (FALSE);
		var_len = ft_varlen(var_line);
		if (var_len)
		{
			//if (is_var_in_env(var_line))
			var = gc_strndup(&d.gc, var_line, var_len);
			unset_var_in_env(var);
			gc_free_item(&d.gc, var);
			append_tab(&d.env, var_line);
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


	/*
int	ft_cd(t_token *token)
{
	char	*path;
	char	cwd[1024];
	char	*env_line;

	(void)path;
	(void)token;
	(void)	cwd;
	(void)	env_line;
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
	//if (getcwd(cwd, sizeof(cwd)) != NULL)
	//unset_var_in_env("OLDPWD");
	//get
	//ft_setenv(
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
*/

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
			gc_free_item(&d.gc, oldpwd); // Free oldpwd before returning
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
