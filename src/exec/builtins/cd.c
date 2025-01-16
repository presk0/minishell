/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:29:30 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/16 17:43:24 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_new_pwd(char **local_env, char *new_path);
static char	*compute_new_pwd(char *new_pwd, char *step);

char	**ini_paths(char **local_env, int *error, char **cmd, char **new_path)
{
	char	**to_export;

	if (ft_strncmp(cmd[1], "/home/", 6) == 0 || ft_strncmp(cmd[1], "/home\0", 6) == 0)
		*new_path = ft_strdup(cmd[1]);
	else
	{
		*new_path = ft_strjoin(ft_getenv(gc, local_env, "PWD"), "/");
		if (!*new_path)
			return (*error = 2, NULL);
		*new_path = ft_strjoin_free1(*new_path, cmd[1]);
	}
	if (!*new_path)
		return (*error = 2, NULL);
	to_export = ft_calloc(sizeof(char **), 4);
	if (!to_export)
		return (*error = 2, NULL);
	to_export[0] = ft_strdup("export");
	if (to_export[0] == NULL)
	{
		free(to_export);
		return (*error = 2, NULL);
	}
	to_export[1] = ft_strjoin("OLDPWD=", ft_getenv(local_env, "PWD"));
	if (to_export[1] == NULL)
	{
		free_tab(to_export);
		return (*error = 2, NULL);
	}
	return (to_export[3] = NULL, to_export);
}

int	ft_cd(char **local_env, char **cmd)
{
	char	**export;
	char	*new_path;
	int		error;
	char	*new_path_part2;	

	error = 0;
	if (cmd[1] && cmd[2])
		return (ft_print_err("minishell : cd: too many arguments"), 1);
	if (!cmd[1] || ft_strcmp(cmd[1], "~") == 0)
		return (ft_cd_tilde(local_env));
	else if (cmd && cmd[1][0] == '/' && cmd[1][1] == '/' && cmd[1][0] == '\0')
		return (ft_cd_slash(local_env, cmd));
	export = ini_paths(local_env, &error, cmd, &new_path);
	if (chdir(new_path) != 0)
		return (free(new_path), free_tab(export), ft_print_err("No such file or directory\n"), 1);
	new_path_part2 = get_new_pwd(local_env, cmd[1]);
	if (!new_path_part2)
		return (2);
	export[2] = ft_strjoin("PWD=", new_path_part2);
	free(new_path_part2);
	if (!export[2])
		return (free_tab(export), 2);
	free(new_path);
	ft_export(local_env, export);
	return (0);
}

static char	*get_new_pwd(char **local_env, char *new_path)
{
	char	*new_pwd;
	char	**steps;
	int		i;

	if (ft_strncmp(new_path, "/home/", 6) == 0 || ft_strncmp(new_path, "/home\0", 6) == 0)
		new_pwd = ft_strdup("");
	else
		new_pwd = ft_strdup(ft_getenv(local_env, "PWD"));
	if (!new_pwd)
		return (NULL);
	steps = ft_split(new_path, '/');
	if (!steps)
		return (free(new_pwd), NULL);
	i = 0;
	while (steps[i] != NULL && new_pwd != NULL)
	{
		new_pwd = compute_new_pwd(new_pwd, steps[i]);
		i++;
	}
	free_split(steps);
	return (new_pwd);
}

static char	*compute_new_pwd(char *new_pwd, char *step)
{
	char	*tmp;
	size_t	size;

	if (ft_strcmp(step, "..") == 0)
	{
		size = ft_strlen(new_pwd) - ft_strlen(ft_strrchr(new_pwd, '/'));
		tmp = ft_substr(new_pwd, 0, size);
		free(new_pwd);
		if (!tmp)
			return (NULL);
		new_pwd = tmp;
	}
	else
	{
		new_pwd = ft_strjoin_free1(new_pwd, "/");
		if (!new_pwd)
			return (NULL);
		new_pwd = ft_strjoin_free1(new_pwd, step);
		if (!new_pwd)
			return (NULL);
	}
	return (new_pwd);
}
