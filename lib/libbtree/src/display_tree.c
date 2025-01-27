/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   display_tree.c										:+:	  :+:	:+:   */
/*													+:+ +:+			+:+	 */
/*   By: supersko <supersko@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2022/04/07 17:24:45 by supersko			#+#	#+#			 */
/*   Updated: 2025/01/02 17:29:47 by nidionis			###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "btree.h"

void	print_tree(t_btree *root, int space, void (*print)(void *content))
{
	int	i;

	if (!root)
		return ;
	print_tree(root->right, space + 3, print);
	i = 0;
	while (i++ < space)
		printf(" ");
	if (root->content)
		print(root->content);
	printf("\n");
	print_tree(root->left, space + 3, print);
}

void	display_tree(t_btree *root, void (*print)(void *content))
{
	print_tree(root, 0, print);
}
