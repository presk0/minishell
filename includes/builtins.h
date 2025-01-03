/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:37:21 by nkieffer          #+#    #+#             */
/*   Updated: 2024/11/21 19:31:18 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//			echo.c
int		ft_echo(char **args);
//			cd.c
int		ft_cd(t_env *local_env, char **cmd);
int		ft_cd_tilde(t_env *local_env);
int		ft_cd_slash(t_env *local_env, char **cmd);
//			pwd.c
int		ft_pwd(t_env *local_env);
//			export.c
int		ft_export(t_env *local_env, char **cmd);
void	add_in_export(t_env *local_env, char *content);
void	replace_in_export(t_export *export, t_export *new_node);
//			export_utils.c
void	add_in_vars(t_env *local_env, char *content);
void	replace_in_vars(t_env *local_env, char *content);
//			unset.c
int		ft_unset(t_env *local_env, t_command_exec *cmd);
void	rm_in_export(t_env *local_env, char *content);
void	rm_in_env(t_env *local_env, char *content);
void	rm_in_vars(t_env *local_env, char *content);
//			env.c
int		ft_env(t_env *local_env);
void	add_in_env(t_env *local_env, char *content);
void	replace_in_env(t_env *local_env, char *content);
//			exit.c
int		ft_exit(t_minishell *m, t_command_exec *cmd);