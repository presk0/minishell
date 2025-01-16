/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_env.h                                           :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/17 18:29:57 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 11:54:19 by nidionis         ###   ########.fr       */
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
void		free_env(t_list *gc, t_env *local_env);
void		free_export(t_list *gc, t_export *first);
void		free_export_node(t_list *gc, t_export *to_free);

//		ft_getenv.c
char		*ft_getenv(t_list *gc, char **env, char *to_find);

//		init_env.c
t_env		*init_env(t_list *gc, char *env[]);
char		**cpy_env(t_list *gc, char *env[]);
char		**init_null_env(t_list *gc);

//		init_export.c
t_export	*init_export(t_list *gc, char *env[]);
t_export	*export_new_node(t_list *gc, char *content);
t_export	*export_new_deminode(t_list *gc, char *content);

//		init_export_utils.c
void		sort_export(t_list *gc, t_export **first);
void		swap_first(t_list *gc, t_export **first);
void		swap_next(t_list *gc, t_export *first);

//		print_env.c
void		print_env(t_list *gc, t_env *local_env);
void		print_export(t_list *gc, t_env *local_env);

#endif
