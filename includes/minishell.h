/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   minishell.h										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <nidionis@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/12/17 16:26:37 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/04 15:50:37 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libft/include/libft.h"
# include "../lib/libgc/include/libgc.h"
# include "../lib/libbtree/include/btree.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/wait.h>
# include "ft_env.h"

# define PS1 "$"
# define TOKEN_PIPE 0
# define TOKEN_REDIR_IN 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_HEREDOC 3
# define TOKEN_APPEND 4

# define LEFT 0
# define RIGHT 1

# define BUFF_QUOTE_MAX 10
# define BUFF_TOK_CMD 0
# define BUFF_STRLEN 1
# define BUFF_STRNSTR 2
# define RESET 99
# define SAVE 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define HERE_DOC 3
# define REDIR_APPEND 4
# define WHITE_SPACE " \t\n\r\v"

typedef struct	s_token
{
	char	*cmd;
	char	**args;
	char	*redir_in;
	char	*redir_out;
	int		append_flag;
	int		heredoc;
}	t_token;

typedef struct btree_content
{
	char	*cmd;
	t_token	token;
}	t_btree_content;

typedef struct s_data
{
	t_list	*gc;
	t_btree	*tree;
	t_env	*env;
}	t_data;

char	*substr_left(t_list *gc, char *node_content, char *found);
char	*substr_right(t_list *gc, char *node_content, char *found);
int		is_quoted(char c, int buff, int reset);
char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len);
void	split_node(t_list *gc, t_btree *root, char *sep);
void	btree_split(t_list *gc, t_btree *root, char *sep);
void	free_node_content(void *stuff);
void	print_node_content(void *content);
void	minishell_exit(t_list *gc);
char	*end_of_word(char *str);
size_t	substitute_var(char *str, t_list *gc);
void	run_line(t_list *gc, char *line, t_env *env);
t_btree_content	*new_content(t_list *gc);
t_btree	*new_node(t_list *gc, t_btree_content *content);
int	check_childs_rec(t_list *gc, t_btree *root);
int	check_childs(t_list *gc, t_btree *root);
int	is_operand(char *cmd);
int	strlen_wd_quoted(char *cmd);
char	*save_token_op(t_list *gc, char *cmd, int op, t_token *token);
void	print_token(t_token	*token);
t_token	*init_token(t_list *gc);
t_token	*tokenize_cmd(t_list *gc, char *cmd, t_token *token);
void handle_sigint(int sig);
void init_sig(t_list *gc);
void	process_pipe(t_list *gc, t_token *cmd);
void rec_exec(t_list *gc, t_btree *node, t_env *env);
void rec_tokenization(t_list *gc, t_btree *node, t_env *env);
int	is_pipe(t_btree *node);
void gc_free_node_content(t_list **gc, void *content);
void gc_free_tree(t_list **gc, t_btree **r, void (*f_free)(t_list **gc, void *content));
void	exec_cmd(t_list *gc, t_token *tok, t_env *env);
void	exec_forking(t_list *gc, t_btree *root, t_env *env);
int open_redirect(char *file, int mode);
void handle_redir_in(t_token *tok);
void handle_redir_out(t_token *tok);
int	is_operand(char *cmd);
char	*skip_operand(char *cmd, char op);
char	*skip_op_and_arg(char *str, char op);
char	*grep_token(t_list *gc, char op, char *cmd);
char	*save_token_op(t_list *gc, char *cmd, int op, t_token *token);
char	*strdup_wd_quote(t_list *gc, char *cmd);
void	append_tab(t_list *gc, char ***tab_addr, char *str);

#endif
