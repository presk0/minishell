/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:29:39 by nkieffer          #+#    #+#             */
/*   Updated: 2024/11/21 19:30:13 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_tilde(t_env *local_env)
{
	char	**export;
	char	*new_path;

	export = ft_calloc(sizeof(char **), 4);
	export[0] = ft_strdup("export");
	if (export[0] == NULL)
		return (2);
	if (!export)
		return (2);
	export[1] = ft_strjoin("OLDPWD=", ft_getenv(local_env, "PWD"));
	if (!export[1])
		return (2);
	export[3] = NULL;
	new_path = ft_strjoin("/home/", ft_getenv(local_env, "LOGNAME"));
	if (!new_path)
		return (2);
	if (chdir(new_path) != 0)
		return (free(new_path), free_tab(export), ft_print_err("No such file or directory\n"), 1);
	export[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!export[2])
		return (2);
	free(new_path);
	return (ft_export(local_env, export));
}

int	ft_cd_slash(t_env *local_env, char **cmd)
{
	char	**export;
	char	*new_path;

	export = ft_calloc(sizeof(char **), 4);
	export[0] = ft_strdup("export");
	if (export[0] == NULL)
		return (2);
	if (!export)
		return (2);
	export[1] = ft_strjoin("OLDPWD=", ft_getenv(local_env, "PWD"));
	if (!export[1])
		return (2);
	export[3] = NULL;
	if (cmd[1][0] == '/' && cmd[1][1] != '/')
		new_path = ft_strjoin("/", ft_strrchr(cmd[1], '/'));
	else
		new_path = ft_strdup(ft_strrchr(cmd[1], '/'));
	if (chdir(new_path) != 0)
		return (free(new_path), free_tab(export), ft_print_err("No such file or directory\n"), 1);
	export[2] = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (!export[2])
		return (2);
	free(new_path);
	ft_export(local_env, export);
	return (0);
}
