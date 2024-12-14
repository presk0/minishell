/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: supersko <supersko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 17:24:45 by supersko          #+#    #+#             */
/*   Updated: 2024/12/08 14:40:01 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <stdlib.h>
# include <stdio.h>
# define LEFT 0
# define RIGHT 1

typedef struct s_btree
{
	void			*content;
	struct s_btree		*left;
	struct s_btree		*right;
}	t_btree;

t_btree	*btree_create_node(void *content);
void	btree_apply_inorder(t_btree *root, void (*applyf)(void *));
void	print_node_content(void *content);

#endif
