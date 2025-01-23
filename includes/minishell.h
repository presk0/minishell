/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/01/23 21:25:17 by nidionis         ###   ########.fr       */
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

# define PS1 "$ "
# define TOKEN_PIPE 0
# define TOKEN_REDIR_IN 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_HEREDOC 3
# define TOKEN_APPEND 4

# define LEFT 0
# define RIGHT 1
# define FALSE 0
# define TRUE 1

# define BUFF_TOK_CMD 0
# define BUFF_STRLEN 1
# define BUFF_STRNSTR 2
# define BUFF_SUBVAR 3
# define BUFF_RMQUOTES 4
# define BUFF_QUOTE_MAX 5
# define SAVE 0
# define READ 1
# define RESET 2

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

# define NO_QUOTE 0
# define SIMPLE_QUOTE 1
# define DOUBLE_QUOTE 2

# define CLEAN_EXIT 0
# define ERR_GC_STRDUP -99
# define ERR_GC_APPEND -98
# define CHILD_INTERRUPT -97
# define CMD_NOT_FOUND 127

typedef struct	s_data
{
	char	**env;
	t_list	*gc;
	t_btree	*cmd_tree;
	int		status;
} t_data;

extern t_data d;

typedef struct	s_token
{
	char	*cmd;
	char	**args;
	int		cmd_id;
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

char	*substr_left(char *node_content, char *found);
char	*substr_right(char *node_content, char *found);
int		is_quoted(char c, int buff, int reset);
char	*ft_strnstr_quotes(const char *str, const char *ndl, size_t len);
void	split_node(t_btree *root, char *sep);
void	btree_split(t_btree *root, char *sep);
void	free_node_content(void *stuff);
void	print_node_content(void *content);
void	minishell_exit();
char	*end_of_word(char *str);
size_t	substitute_var(char *str);
void	run_line(char *line);
t_btree_content	*gc_malloc_btree_content();
t_btree	*new_node(t_btree_content *content);
int	check_childs_rec(t_btree *root);
int	check_childs(t_btree *root);
int	is_operand(char *cmd);
int	strlen_wd_quoted(char *cmd);
char	*save_token_op(char *cmd, int op, t_token *token);
void	print_token(t_token	*token);
t_token	*init_token();
t_token	*tokenize_cmd(char *cmd, t_token *token);
void handle_sigint(int sig);
void init_sig();
void	process_pipe(t_token *cmd);
void rec_exec(t_btree *node);
void rec_tokenization(t_btree *node);
int	is_pipe(t_btree *node);
void gc_free_node_content(t_list *gc, void *content);
void gc_free_tree(t_list *gc, t_btree **cmd_tree, void (*f_free)(t_list *gc, void *content));
void	exec_cmd(t_token *tok);
int		exec_forking(t_btree *root);
int open_redirect(char *file, int mode);
void handle_redir_in(t_token *tok);
void handle_redir_out(t_token *tok);
int	is_operand(char *cmd);
char	*skip_operand(char *cmd, char op);
char	*skip_op_and_arg(char *str, char op);
char	*grep_token(char op, char *cmd);
char	*save_token_op(char *cmd, int op, t_token *token);
char	*strdup_wd_quote(char *cmd);
void	append_tab(char ***tab_addr, char *str);
int	exec_whole_line(t_btree *cmd_tree);
void    *gc_realloc(void *ptr, size_t old_size, size_t new_size);
char	*substitute_variables(char *input);
int	strlen_char_quoted(char *cmd, char c);
//void	append_until_dollar(char *input, size_t *i, char *result);
char	*process_dollar(char *input, size_t *i_input, size_t *i_result, char **result);
size_t	append_until_dollar(char *input, size_t *i_input, size_t *i_result, char **result);
//size_t	gc_strlcat(char **result, char *str);
char	*ft_getenv(const char *var);
int	ft_varlen(const char *var);
char	*rm_quotes(char *str);
char	*del_char(char *str);
char	*subst_var_and_quotes(char *str);
void	prepend_path(char **cmd);
void	substitute_var_in_token(t_token *token);

void init_child_sig();
void wait_for_child(pid_t pid);
#endif
