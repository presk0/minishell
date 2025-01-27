/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   btree.h											:+:		:+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: supersko <supersko@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2022/04/07 17:24:45 by supersko			#+#	#+#			 */
/*   Updated: 2024/12/18 13:16:52 by nidionis			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

# include <stdio.h>
# include <stdlib.h>
# define LEFT 0
# define RIGHT 1
# define ROOT 2

typedef struct s_btree
{
	void			*content;
	struct s_btree	*left;
	struct s_btree	*right;
}					t_btree;

t_btree				*btree_create_node(void *content);
void				btree_apply_inorder(t_btree *root, void (*applyf)(void *));
void				display_tree(t_btree *root, void (*print)(void *content));
void				free_tree(t_btree *root, void (*f_free)(void *content));
void				btree_apply_prefix(t_btree *root,
						void *(*applyf)(t_btree *node));
void				btree_apply_postfix(t_btree *root,
						void *(*applyf)(t_btree *node));
void				btree_apply_infix(t_btree *root,
						void *(*applyf)(t_btree *node));

#endif
