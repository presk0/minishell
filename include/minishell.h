#ifndef MINISHELL_H
# define MINISHELL_H
# include <libft.h>
# include <libgc.h>
# include <btree.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PS1 ">"
# define TOKEN_PIPE 0
# define TOKEN_REDIR_IN 1
# define TOKEN_REDIR_OUT 2
# define TOKEN_HEREDOC 3
# define TOKEN_APPEND 4

typedef struct btree_content
{
    char	*cmd;
    char    *token;
}	t_btree_content;

#endif
