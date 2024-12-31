/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 15:51:11 by supersko          #+#    #+#             */
/*   Updated: 2024/12/31 14:17:14 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGC_H
# define LIBGC_H
# include "../../libft/include/libft.h"

void	*gc_append(t_list **gc_addr, void *ptr);
void	gc_free_all(t_list **gc_addr);
void	*gc_malloc(t_list **gc_addr, size_t count, size_t size);
void	gc_free_item(t_list **gc_addr, void *ptr);

#endif
