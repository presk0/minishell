/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   template.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2024/09/05 14:15:32 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	is_pipe(t_btree *node)
{
	t_btree_content	*c;

	c = node->content;
	return (!ft_strncmp(c->cmd, "|", 1));
}

void	tokenize_content(t_list *gc, t_btree *node, char **envp)
{
	(void)envp;
	t_btree_content *content = node->content;
	t_token *tok = &(content->token);
	tokenize_cmd(gc, content->cmd, tok);
}

void rec_tokenization(t_list *gc, t_btree *node, char **envp)
{
	if (!node)
		return;
	if (is_pipe(node))
	{
		rec_tokenization(gc, node->left, envp);
		rec_tokenization(gc, node->right, envp);
	}
	else
		tokenize_content(gc, node, envp);
}
