/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2024/12/18 17:47:05 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libft/include/libft.h"
# include "../lib/libgc/include/libgc.h"
# include "../lib/libbtree/include/btree.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "ft_env.h"

# define PS1 ">"
# define TOKEN_PIPE 0
# define TOKEN_REDIR_IN 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_HEREDOC 3
# define TOKEN_APPEND 4

typedef struct btree_content
{
	char	*cmd;
	char	*token;
}	t_btree_content;


void	split_node(t_btree *root, char *sep);
void	btree_split(t_btree *root, char *sep);
void	free_node_content(void *stuff);
void	print_node_content(void *content);
char	*substr_left(char *node_content, char *found);
char	*substr_right(char *node_content, char *found);
int		is_quoted(char c, int reset);
char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len);

#endif
