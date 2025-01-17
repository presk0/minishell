/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/17 19:19:56 by nidionis         ###   ########.fr       */
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
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/wait.h>

# define PS1 "$"
# define TOKEN_PIPE 0
# define TOKEN_REDIR_IN 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_HEREDOC 3
# define TOKEN_APPEND 4

# define LEFT 0
# define RIGHT 1
# define FALSE 0
# define TRUE 1

# define BUFF_QUOTE_MAX 10
# define BUFF_TOK_CMD 0
# define BUFF_STRLEN 1
# define BUFF_STRNSTR 2
# define BUFF_SUBVAR 3
# define RESET 99
# define SAVE 0
# define REDIR_IN 1
# define REDIR_OUT 2
# define HERE_DOC 3
# define REDIR_APPEND 4
# define WHITE_SPACE " \t\n\r\v"

# define ECHO_ID 1
# define CD_ID 2
# define PWD_ID 3
# define EXPORT_ID 4
# define UNSET_ID 4
# define ENV_ID 5
# define EXIT_ID 6
# define MINISHELL_ID 7

typedef struct	s_token
{
	char	*cmd;
	char	**args;
	int		cmd_id;
	//char	**arg;
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
void	run_line(t_list *gc, char *line, char **env);
t_btree_content	*gc_malloc_btree_content(t_list *gc);
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
void rec_exec(t_list *gc, t_btree *node, char **env);
void rec_tokenization(t_list *gc, t_btree *node, char **env);
int	is_pipe(t_btree *node);
void gc_free_node_content(t_list **gc, void *content);
void gc_free_tree(t_list **gc, t_btree **r, void (*f_free)(t_list **gc, void *content));
void	exec_cmd(t_list *gc, t_token *tok, char **env);
int		exec_forking(t_list *gc, t_btree *root, char **env);
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
int	exec_whole_line(t_list *gc, t_btree *cmd_tree, char **env);
void    *gc_realloc(t_list *gc, void *ptr, size_t old_size, size_t new_size);
char	*substitute_variables(t_list *gc, char *input, char **env);
int	strlen_char_quoted(char *cmd, char c);
void	append_until_dollar(t_list *gc, char *input, size_t *i, char *result);
char	*process_dollar(t_list *gc, char *input, size_t *i, char **env, char *result);
size_t	gc_str_append(t_list *gc, char **result, char *str);
char	*ft_getenv(char **env, const char *var);
int	ft_varlen(const char *var);

#endif