/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/03 15:27:12 by nidionis         ###   ########.fr       */
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
# define RESET 1
# define SAVE 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define HERE_DOC 3
# define REDIR_APPEND 4
# define WHITE_SPACE " \t\n\r\v"

typedef struct	s_token
{
	char	*cmd;
	char	**arg;
	char	*redir_in;
	char	*redir_out;
	int		append_flag;
}	t_token;

typedef struct btree_content
{
	char	*cmd;
	t_token	token;
}	t_btree_content;

char	*substr_left(t_list *gc, char *node_content, char *found);
char	*substr_right(t_list *gc, char *node_content, char *found);
int		is_quoted(char c, int reset);
char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len);
void	split_node(t_list *gc, t_btree *root, char *sep);
void	btree_split(t_list *gc, t_btree *root, char *sep);
void	free_node_content(void *stuff);
void	print_node_content(void *content);
void	minishell_exit(t_list *gc);
char	*end_of_word(char *str);
size_t	substitute_var(char *str, t_list *gc);
void	apply_cmd(char *line, t_list *gc);
void	minishell(void);
t_btree_content	*new_content(t_list *gc);
t_btree	*new_node(t_list *gc, t_btree_content *content);
int	check_childs_rec(t_list *gc, t_btree *root);
int	check_childs(t_list *gc, t_btree *root);
int	is_operand(char *cmd);
int	strlen_wd_quoted(char *cmd);
char	*save_token_op(t_list *gc, char *cmd, int op, t_token *token);

#endif
