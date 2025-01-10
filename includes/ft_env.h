/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_env.h										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/17 18:29:57 by nkieffer		  #+#	#+#			 */
/*   Updated: 2024/12/17 18:44:26 by nkieffer		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef FT_ENV_H
# define FT_ENV_H

# include "minishell.h" 

typedef struct s_export
{
	char			*line;
	struct s_export	*next;
}	t_export;

typedef struct s_env
{
	char		**my_env;
	t_export	*my_export;
}	t_env;

//		free_env.c
void		free_env(t_env *local_env);
void		free_export(t_export *first);
void		free_export_node(t_export *to_free);

//		ft_getenv.c
char		*ft_getenv(char **env, char *to_find);

//		init_env.c
t_env		*init_env(char *env[]);
char		**cpy_env(char *env[]);
char		**init_null_env(void);

//		init_export.c
t_export	*init_export(char *env[]);
t_export	*export_new_node(char *content);
t_export	*export_new_deminode(char *content);

//		init_export_utils.c
void		sort_export(t_export **first);
void		swap_first(t_export **first);
void		swap_next(t_export *first);

//		print_env.c
void		print_env(t_env *local_env);
void		print_export(t_env *local_env);
#endif