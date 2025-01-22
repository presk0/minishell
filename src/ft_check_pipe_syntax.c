/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   template.c											:+:		:+:	:+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2024/09/05 14:15:32 by nidionis			###   ########.fr		*/
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	check_childs_rec(t_btree *root)
{
	if (!root)
		return (0);
	if ((root->right && !root->left) || (!root->right && root->left))
		return (0);
	if (root->right && !check_childs_rec(root->right))
		return (0);
	if (root->left && !check_childs_rec(root->left))
		return (0);
	if (!root->right && !root->left && is_pipe(root))
		return (0);
	return (1);
}

int	check_childs(t_btree *root)
{
	int	each_nodes_have_two_childs;

	each_nodes_have_two_childs = check_childs_rec(root);
	if (!each_nodes_have_two_childs)
		printf("bash: syntax error near unexpected token `|'\n");
	return (each_nodes_have_two_childs);
}
