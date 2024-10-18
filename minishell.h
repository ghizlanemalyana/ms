/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:37:40 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/18 23:52:42 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\033[0;35m➜\033[0m "

// Debug
# define TRUE "\033[0;32mtrue\033[0m"
# define FALSE "\033[0;31mfalse\033[0m"

# define ERROR 258
# define SUCCESS 0
# define FAILURE 1

# define WRITE_FD 0
# define READ_FD 1

extern int	g_received_signals;

typedef enum e_type
{
	NONE,
	PIPE,
	ARG,
	REDIR_OUT,
	REDIR_IN,
	APPEND,
	HEREDOC
}	t_type;

typedef struct s_env
{
	char		*key;
	char		*value;
}	t_env;

typedef struct s_token
{
	char		*content;
	int			len;
	int			type;
	bool		quoted;
	bool		linked;
	bool		expandable;
}	t_token;

typedef struct s_redir
{
	int			fd;
	char		*filename;
	t_type		type;
}	t_redir;

typedef struct s_cmd
{
	int			argc;
	char		**argv;
	t_list		*redirs;
}	t_cmd;

/*
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;
*/

typedef struct s_shell
{
	t_list		*tokens;
	t_list		*cmds;
	t_list		*env;
	int			exit_status;
	int			received_signals;
}	t_shell;


// t_type		get_type(char *word);
// int			get_len(char *word, t_type type);

// Builtins
int			ft_echo(t_shell *sh, char **av);
int			ft_cd(t_shell *sh, char **av);
int			ft_pwd(t_shell *sh, char **av);
int			ft_export(t_shell *sh, char **av);
int			ft_unset(t_shell *sh, char **av);
int			ft_env(t_shell *sh, char **av);
int			ft_exit(t_shell *sh, char **av);
bool		is_valid_key(char *key);

// Parsing
void		free_token(void *content);
int			parse(t_shell *sh);
bool		is_expandable(char *line);
int 		expand(t_shell *sh, t_token *token);

// Signals
void		sigint_handler(int sig);
int 		init_cmd(t_shell *sh);
// Environment
void		free_env(void *content);
t_env		*new_env(char *env);
char		*get_env(t_list *list, char *key);
int 		init_env(t_list **list, char **envp);

void		print_tokens(t_list *tokens);
void		display_cmds(t_list *cmd);
void		free_cmd(void *content);
bool		isredir(t_token *token);

// Expansion
char		*expand_string(t_shell *sh, char *line);

// Heredoc
int	set_heredoc(t_shell *sh, t_redir *redir, t_token *token);

// Utils
char		*ft_strjoin_free(char *s1, char *s2, int to_free);
bool		isoperator(t_token *token);
bool		isredir(t_token *token);

# endif