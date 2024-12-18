/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2024/12/18 13:30:09 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGC_H
# define LIBGC_H
# include <libft.h>

void	*gc_append(t_list **gc_addr, void *ptr);
void	clean_exit(t_list **gc_addr);
void	*gc_malloc(t_list **gc_addr, size_t count, size_t size);
void	gc_free_item(t_list **gc_addr, void *ptr);

#endif
