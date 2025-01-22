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

int	is_pipe(t_btree *node)
{
	t_btree_content	*c;

	c = node->content;
	return (!ft_strncmp(c->cmd, "|", 1));
}

void	tokenize_content(t_btree *node)
{
	t_btree_content	*content;
	t_token			*tok;

	content = node->content;
	tok = &(content->token);
	tokenize_cmd(content->cmd, tok);
	// substitute_var_in_token(tok);
}

void	rec_tokenization(t_btree *node)
{
	if (!node)
		return ;
	if (is_pipe(node))
	{
		rec_tokenization(node->left);
		rec_tokenization(node->right);
	}
	else
		tokenize_content(node);
}