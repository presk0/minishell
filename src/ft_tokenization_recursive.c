/* ************************************************************************** */
/*																			*/
/*														:::		::::::::   */
/*   ft_tokenization_recursive.c                        :+:      :+:    :+:   */
/*													+:+ +:+			+:+		*/
/*   By: nidionis <marvin@42.fr>					+#+  +:+		+#+		*/
/*												+#+#+#+#+#+   +#+			*/
/*   Created: 2024/09/04 16:20:59 by nidionis			#+#	#+#				*/
/*   Updated: 2025/02/04 00:23:20 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include <minishell.h>

int	is_pipe(t_btree *node)
{
	t_btree_content	*c;

	c = node->content;
	return (!ft_strncmp(c->cmd, "|", 1));
}

void	substitute_var_in_token(t_data *d, t_token *token)
{
	int	i;

	token->cmd = subst_var_and_quotes(d, token->cmd);
	i = 0;
	while (token->args && token->args[i])
	{
		token->args[i] = subst_var_and_quotes(d, token->args[i]);
		i++;
	}
	token->redir_in = subst_var_and_quotes(d, token->redir_in);
	token->redir_out = subst_var_and_quotes(d, token->redir_out);
}

void	tokenize_content(t_data *d, t_btree *node)
{
	t_btree_content	*content;
	t_token			*token;

	content = node->content;
	token = &(content->token);
	tokenize_cmd(d, content->cmd, token);
}

void	rec_tokenization(t_data *d, t_btree *node)
{
	if (!node)
		return ;
	if (is_pipe(node))
	{
		rec_tokenization(d, node->left);
		rec_tokenization(d, node->right);
	}
	else
		tokenize_content(d, node);
}
