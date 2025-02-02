/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nidionis <nidionis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:26:37 by nkieffer          #+#    #+#             */
/*   Updated: 2025/02/02 23:15:59 by nidionis         ###   ########.fr       */
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

extern t_data	g_d;

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

void			set_cmd_id(t_token *token);
int				exec_builtin(t_token *token);
int				exec_builtin_scotch(t_btree *node);
int				is_builtin(t_token *token);
char			*get_target_directory(t_token *token);
int				handle_directory_access(char *target_dir);
int				change_directory(char *target_dir);
void			update_env_variables(char *oldpwd, char *cwd);
int				ft_cd(t_token *token);
char			*shift_char(char *str, size_t shift_len);
char			*shift_left(char *str, size_t shift_len);
int				check_childs_rec(t_btree *root);
int				check_childs(t_btree *root);
void			reset_stdin(int stdin_fd);
void			save_stds(int *saved_std);
void			restore_stds(int *saved_std);
int				ft_echo(t_token *token);
void			remove_var_from_env(char **env, int index);
int				unset_var_in_env(char *var);
int				ft_unset(t_token *token);
int				ft_setenv(char *var_line);
int				find_var_index(char **env, char *var, size_t var_len);
int				ft_env(void);
char			*ft_getenv_line(const char *var);
char			*ft_getenv(const char *var);
void			execve_node(t_btree *node);
int				exec_forking(t_btree *node);
void			run_line(char *line);
int				exec_whole_line(void);
void			execute_command(t_btree *node);
void			rec_exec(t_btree *node);
int				ft_exit(t_token *token);
void			print_export(char **tab);
void			ft_swap(char **a, char **b);
void			ft_easy_sort(char ***t);
int				ft_export(t_token *token);
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
char			*grep_token(char op, char *cmd);
char			*save_and_skip_redir_out(char *cmd, t_token *token);
char			*save_and_skip_redir_in(char *cmd, t_token *token);
char			*save_and_skip_here_doc(char *cmd, t_token *token);
char			*save_and_skip_redir_append(char *cmd, t_token *token);
char			*save_token_op(char *cmd, int op, t_token *token);
int				is_blank(char *str);
char			*substr_left(char *node_content, char *found);
char			*substr_right(char *node_content, char *found);
void			split_node(t_btree *root, char *sep);
void			btree_split(t_btree *root, char *sep);
void			pipe_left(t_btree *node, int pipe_fd[]);
void			pipe_right(t_btree *node, int pipe_fd[]);
int				ft_pwd(t_token *token);
char			*del_char(char *str);
char			*rm_quotes(char *str);
int				strlen_char_simple_quoted(char *cmd, char c, int buff);
int				strlen_wd_quoted(char *cmd);
char			*strdup_wd_quote(char *cmd);
int				is_quoted(char c, int buff, int action);
char			*ft_strnstr_quotes(const char *str, const char *ndl,
					size_t len);
int				open_redirect(char *file, int mode);
void			handle_redir_in(t_token *tok);
int				handle_eoheredoc(int pipe_fd[2]);
void			handle_redir_out(t_token *tok);
void			forked_sig(void);
void			handle_sigint(int sig);
void			init_sig(void);
void			wait_for_child(pid_t pid);
void			append_tab(char ***tab_addr, char *str);
int				is_pipe(t_btree *node);
void			substitute_var_in_token(t_token *token);
void			tokenize_content(t_btree *node);
void			rec_tokenization(t_btree *node);
void			prepend_path(char **cmd);
char			*save_token_cmd(char *cmd, t_token *token);
t_token			*tokenize_cmd(char *cmd, t_token *token);
void			print_token(t_token *token);
void			gc_free_node_content(t_list *gc, void *content);
void			print_node_content(void *content);
t_btree_content	*gc_malloc_btree_content(void);
t_btree			*new_node(t_btree_content *content);
void			free_token(t_token token);
size_t			var_len(char *var);
int				ft_varlen(const char *var);
int				is_valid_var_name(const char *var);
int				is_var_in_env(const char *var);
char			*subst_var_and_quotes(char *str);
int				is_to_substitute(char *var);
char			*substitute_variables(char *input);
void			*gc_realloc(void *ptr, size_t old_size, size_t new_size);
char			*gc_strjoin(const char *s1, const char *s2);
char			*pop_line(char *buff);
char			*clean_lines(char **next_line, char **buff);
char			*load_until_line(int fd, char **buff);
char			*get_next_line(int fd);

void			gc_free_tree(t_list *gc, t_btree **r, void (*f_free)(t_list *gc,
						void *content));
size_t			append_until_dollar(char *input, size_t *i_input,
					size_t *i_result, char **result);
char			*process_dollar(char *input, size_t *i_input, size_t *i_result,
					char **result);
char			*ft_strnstr_quotes(const char *str, const char *ndl,
					size_t len);
void			minishell_exit(char *errmsg, int status);
char			**duplicate_tab(char **tab_original);
void			inc_shlvl(void);
void			minishell(char **envp);
void			print_tab(char **tab);
int				is_quote_opened(char *str);

// void	format_buff(char *buff, char *next_line);
// char	*line_from_buff(char *buff);
// char	*load_until_line(int fd, char **buff);
// char	*get_next_line(int fd);
// void	get_next_line_tester(int argc, char **argv);

#endif
