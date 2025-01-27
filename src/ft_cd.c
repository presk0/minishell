/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/01/27 22:18:25 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_target_directory(t_token *token)
{
	char	*target_dir;

	if (token->args[1] != NULL)
		return (token->args[1]);
	target_dir = ft_getenv("HOME");
	if (target_dir == NULL)
		fprintf(stderr, "cd: HOME not set\n");
	return (target_dir);
}

int	handle_directory_access(char *target_dir)
{
	if (access(target_dir, F_OK) != SUCCESS)
	{
		g_d.status = 1;
		return (FAILURE);
	}
	return (SUCCESS);
}

int	change_directory(char *target_dir)
{
	if (chdir(target_dir) != SUCCESS)
	{
		perror("cd failed");
		return (FAILURE);
	}
	return (SUCCESS);
}

void	update_env_variables(char *oldpwd, char *cwd)
{
	char	*newpwd;

	newpwd = gc_strdup(&g_d.gc, "PWD=");
	gc_strcat(&g_d.gc, &newpwd, cwd);
	ft_setenv(oldpwd);
	ft_setenv(newpwd);
}

int	ft_cd(t_token *token)
{
	char	*target_dir;
	char	oldpwd[1024];
	char	cwd[1024];

	ft_strlcpy(oldpwd, "OLDPWD=", sizeof(oldpwd));
	ft_strlcat(oldpwd, ft_getenv("PWD"), sizeof(oldpwd));

	target_dir = get_target_directory(token);
	if (!target_dir)
		return (FAILURE);
	if (handle_directory_access(target_dir) != SUCCESS)
		return (FAILURE);
	if (change_directory(target_dir) != SUCCESS)
		return (FAILURE);
	getcwd(cwd, sizeof(cwd));
	update_env_variables(oldpwd, cwd);
	g_d.status = 0;
	return (CLEAN_EXIT);
}
