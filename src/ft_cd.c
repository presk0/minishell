/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2025/02/04 00:00:14 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_target_directory(t_data *d, t_token *token)
{
	char	*target_dir;

	if (token->args[1] != NULL)
		return (token->args[1]);
	target_dir = ft_getenv(d, "HOME");
	if (target_dir == NULL)
		fprintf(stderr, "cd: HOME not set\n");
	return (target_dir);
}

int	handle_directory_access(t_data *d, char *target_dir)
{
	if (access(target_dir, F_OK) != SUCCESS)
	{
		d->status = 1;
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

void	update_env_variables(t_data *d, char *oldpwd, char *cwd)
{
	char	*newpwd;

	newpwd = gc_strdup(&d->gc, "PWD=");
	gc_strcat(&d->gc, &newpwd, cwd);
	ft_setenv(d, oldpwd);
	ft_setenv(d, newpwd);
}

int	ft_cd(t_data *d, t_token *token)
{
	char	*target_dir;
	char	oldpwd[1024];
	char	cwd[1024];

	ft_strlcpy(oldpwd, "OLDPWD=", sizeof(oldpwd));
	ft_strlcat(oldpwd, ft_getenv(d, "PWD"), sizeof(oldpwd));
	target_dir = get_target_directory(d, token);
	if (!target_dir)
		return (FAILURE);
	if (handle_directory_access(d, target_dir) != SUCCESS)
		return (FAILURE);
	if (change_directory(target_dir) != SUCCESS)
		return (FAILURE);
	getcwd(cwd, sizeof(cwd));
	update_env_variables(d, oldpwd, cwd);
	d->status = 0;
	return (CLEAN_EXIT);
}
