/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/02/04 01:57:19 by nidionis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../lib/libbtree/include/btree.h"
# include "../lib/libft/include/libft.h"
# include "../lib/libgc/include/libgc.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef MAX_FD
#  define MAX_FD 256
# endif

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
# define SUCCESS 0
# define FAILURE 1

# define BUFF_TOK_CMD 0
# define BUFF_STRLEN 1
# define BUFF_STRNSTR 2
# define BUFF_SUBVAR 3
# define BUFF_RMQUOTES 4
# define BUFF_RDLINES 5
# define BUFF_QUOTE_MAX 6
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
# define UNSET_ID 5
# define ENV_ID 6
# define EXIT_ID 7
# define MINISHELL_ID 8

# define NO_QUOTE 0
# define SIMPLE_QUOTE 1
# define DOUBLE_QUOTE 2

# define CLEAN_EXIT 0
# define ERR_GC_STRDUP -99
# define ERR_GC_APPEND -98
# define CHILD_INTERRUPT -97
# define CMD_NOT_FOUND 127

# define IN 0
# define OUT 1
# define ERR 2
# define STATUS_SIGQUIT 131

typedef struct s_data
{
	char		**env;
	t_list		*gc;
	t_btree		*cmd_tree;
	int			status;
}				t_data;

typedef struct s_token
{
	char		*cmd;
	char		**args;
	int			cmd_id;
	char		*redir_in;
	char		*redir_out;
	int			append_flag;
	int			heredoc;
}				t_token;

typedef struct btree_content
{
	char		*cmd;
	t_token		token;
}				t_btree_content;

typedef struct s_norminette_sucks
{
	char	*input;
	size_t	i_input;
	char	*result;
	size_t	i_result;
}			t_norminette_sucks;

void			sig_default(void);
void			sig_ignores(void);
void			set_cmd_id(t_token *token);
int				exec_builtin(t_data *d, t_token *token);
int				exec_builtin_scotch(t_data *d, t_btree *node);
int				is_builtin(t_token *token);
char			*get_target_directory(t_data *d, t_token *token);
int				handle_directory_access(t_data *d, char *target_dir);
int				change_directory(char *target_dir);
void			update_env_variables(t_data *d, char *oldpwd, char *cwd);
int				ft_cd(t_data *d, t_token *token);
char			*shift_char(char *str, size_t shift_len);
char			*shift_left(char *str, size_t shift_len);
int				check_childs_rec(t_btree *root);
int				check_childs(t_btree *root);
void			reset_stdin(int stdin_fd);
void			save_stds(int *saved_std);
void			restore_stds(int *saved_std);
int				ft_echo(t_data *d, t_token *token);
void			remove_var_from_env(t_data *d, char **env, int index);
int				unset_var_in_env(t_data *d, char *var);
int				ft_unset(t_data *d, t_token *token);
int				ft_setenv(t_data *d, char *var_line);
int				find_var_index(char **env, char *var, size_t var_len);
int				ft_env(t_data *d);
char			*ft_getenv_line(t_data *d, const char *var);
char			*ft_getenv(t_data *d, const char *var);
void			execve_node(t_data *d, t_btree *node);
int				exec_forking(t_data *d, t_btree *node);
void			run_line(t_data *d, char *line);
int				exec_whole_line(t_data *d);
void			execute_command(t_data *d, t_btree *node);
void			rec_exec(t_data *d, t_btree *node);
void			minishell_exit(t_data *d, char *errmsg, int status);
int				ft_exit(t_data *d, t_token *token);
void			print_export(char **tab);
void			ft_swap(char **a, char **b);
void			ft_easy_sort(char ***t);
int				ft_export(t_data *d, t_token *token);
void			handle_dup_failure(int fd, const char *msg);
void			handle_fork_failure(pid_t pid, const char *msg);
void			handle_pipe_failure(int result, const char *msg);
void			close_pipe_ends(int pipe_fd[2]);
void			write_line_to_pipe(int pipe_fd[2], char **line_addr);
int				check_delimiter(char **line_addr, char *delimiter);
int				read_and_write_heredoc(int pipe_fd[2], char *delimiter);
int				handle_heredoc(char *delimiter);
int				is_operand(char *cmd);
char			*skip_operand(char *cmd, char op);
char			*skip_op_and_arg(char *str, char op);
char			*grep_token(t_data *d, char op, char *cmd);
char			*save_and_skip_redir_out(t_data *d, char *cmd, t_token *token);
char			*save_and_skip_redir_in(t_data *d, char *cmd, t_token *token);
char			*save_and_skip_here_doc(t_data *d, char *cmd, t_token *token);
char			*save_and_skip_redir_append(t_data *d, \
													char *cmd, t_token *token);
char			*save_token_op(t_data *d, char *cmd, int op, t_token *token);
int				is_blank(char *str);
char			*substr_left(t_data *d, char *node_content, char *found);
char			*substr_right(t_data *d, char *node_content, char *found);
void			split_node(t_data *d, t_btree *root, char *sep);
void			btree_split(t_data *d, t_btree *root, char *sep);
void			pipe_left(t_data *d, t_btree *node, int pipe_fd[]);
void			pipe_right(t_data *d, t_btree *node, int pipe_fd[]);
int				ft_pwd(t_data *d, t_token *token);
char			*del_char(char *str);
char			*rm_quotes(char *str);
int				is_quote_opened(char *str);
int				strlen_char_simple_quoted(char *cmd, char c, int buff);
int				strlen_wd_quoted(char *cmd);
char			*strdup_wd_quote(t_data *d, char *cmd);
int				is_quoted(char c, int buff, int action);
char			*ft_strnstr_quotes(const char *str, const char *ndl, \
																size_t len);
int				open_redirect(char *file, int mode);
void			handle_redir_in(t_token *tok);
int				handle_eoheredoc(int pipe_fd[2]);
void			handle_redir_out(t_token *tok);
void			handle_sigquit_forked(int sig);
void			sig_ignores(void);
void			handle_sigint(int sig);
void			init_sig(t_data *d);
void			append_tab(t_data *d, char ***tab_addr, char *str);
char			**duplicate_tab(t_data *d, char **tab_original);
int				is_pipe(t_btree *node);
void			substitute_var_in_token(t_data *d, t_token *token);
void			tokenize_content(t_data *d, t_btree *node);
void			rec_tokenization(t_data *d, t_btree *node);
void			prepend_path(t_data *d, char **cmd);
char			*save_token_cmd(t_data *d, char *cmd, t_token *token);
t_token			*tokenize_cmd(t_data *d, char *cmd, t_token *token);
void			print_token(t_token *token);
void			gc_free_node_content(t_list *gc, void *content);
void			print_node_content(void *content);
t_btree_content	*gc_malloc_btree_content(t_data *d);
t_btree			*new_node(t_data *d, t_btree_content *content);
void			free_token(t_list **gc, t_token token);
size_t			var_len(char *var);
int				ft_varlen(const char *var);
int				is_valid_var_name(const char *var);
size_t			append_until_dollar(t_data *d, t_norminette_sucks *v);
char			*process_dollar(t_data *d, t_norminette_sucks *v);
void			*gc_realloc(t_data *d, void *ptr, size_t old_size, \
														size_t new_size);
char			*gc_strjoin(t_data *d, const char *s1, const char *s2);
char			*pop_line(char *buff);
char			*clean_lines(char **next_line, char **buff);
char			*load_until_line(int fd, char **buff);
char			*get_next_line(int fd);
void			inc_shlvl(t_data *d);
char			*subst_var_and_quotes(t_data *d, char *str);
int				is_to_substitute(char *var);
char			*substitute_variables(t_data *d, char *input);
void			gc_free_tree(t_list *gc, t_btree **r, \
								void (*f_free)(t_list *gc, void *content));
int				is_var_in_env(t_data *d, const char *var);

#endif
