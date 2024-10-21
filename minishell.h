/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 11:37:40 by gmalyana          #+#    #+#             */
/*   Updated: 2024/10/21 19:42:13 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <string.h>
# include <stdio.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PROMPT "\033[0;35m➜\033[0m "

//! Debug
# define TRUE "\033[0;32mtrue\033[0m"
# define FALSE "\033[0;31mfalse\033[0m"
void	print_tokens(t_list *tokens);

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
	char		**envp;
	t_list		*redirs;
}	t_cmd;

typedef struct s_shell
{
	t_list		*tokens;
	t_list		*cmds;
	t_list		*env;
	t_list		*hidden_env;
	int			exit_status;
	int			received_signals;
}	t_shell;

// Builtins
void		ft_echo(char **av);
int			ft_cd(t_shell *sh, char **av);
int			ft_pwd(t_shell *sh);
void		ft_env(t_shell *sh);
int			ft_exit(t_shell *sh, int ac, char **av);
bool		is_key_valid(char *key);
int			ft_export(t_shell *sh, char **av);
int 		ft_unset(t_shell *shell, char **av);

// Parsing
void		free_token(void *content);
int			parse(t_shell *sh);
bool		is_expandable(char *line);
int			expand(t_shell *sh, t_token *token);

// Signals
void		heredoc_handler(int sig);
void		set_signals_handlers(void);
void		sigint_handler(int sig);

// Commmands
void		free_cmd(void *content);
int			init_cmd(t_shell *sh);

// Environment
void		free_env(void *content);
int			set_env(t_list **list, char *key, char *value);
int			create_env(t_list **list, char *key, char *value);
void		unset_env(t_list **list, char *key);
int			append_env(t_list **list, char *key, char *value);
char		*get_env(t_list *list, char *key);
int			init_hidden_env(t_shell *sh);

// Expansion
char		*expand_string(t_shell *sh, char *line);

// Heredoc
int			set_heredoc(t_shell *sh, t_redir *redir, t_token *token);

// Utils
char		*ft_strjoin_free(char *s1, char *s2, int to_free);
bool		isoperator(t_token *token);
bool		isredir(t_token *token);
void		free_array(char **array);
void		my_exit(t_shell *sh);

# endif