/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   libgc.h                                            :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/02/24 15:51:11 by supersko		  #+#	#+#			 */
/*   Updated: 2025/01/23 17:35:41 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#ifndef LIBGC_H
# define LIBGC_H
# include "../../libft/include/libft.h"

void	*gc_append(t_list **gc_addr, void *ptr);
void	gc_free_all(t_list **gc_addr);
void	*gc_malloc(t_list **gc_addr, size_t count, size_t size);
void	gc_free_item(t_list **gc_addr, void *ptr);
char	*gc_strdup(t_list **gc_addr, char *str);
size_t	gc_strcat(t_list **gc, char **result, char *str);
char *gc_strldup(t_list **gc, char *str, size_t len);
size_t	gc_strlcat(t_list **gc, char **result, char *str, size_t l);
void print_gc(t_list *gc);

#endif
