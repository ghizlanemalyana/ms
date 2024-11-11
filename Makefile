SOURCES = src/main.c src/signals.c src/utils.c \
		src/builtins/ft_cd.c src/builtins/ft_echo.c src/builtins/ft_env.c src/builtins/ft_exit.c \
		src/builtins/ft_export.c src/builtins/ft_pwd.c src/builtins/ft_unset.c src/builtins/utils.c \
		src/env/env.c src/env/utils.c \
		src/exec/exec.c src/exec/join_path.c src/exec/redirs.c src/exec/run.c src/exec/utils.c \
		src/parse/cmd.c src/parse/expansion.c src/parse/heredoc.c src/parse/parse.c src/parse/token.c \
		src/parse/utils.c
OBJS = $(SOURCES:.c=.o)
LIB_DIR = libft
LIBFT = $(LIB_DIR)/libft.a
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

all: $(LIB_DIR) $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -o $(NAME)

%.o : %.c minishell.h $(LIBFT)
	cc $(CFLAGS) -I /Users/$(USER)/.brew/opt/readline/include -c $< -o $@ 

$(LIB_DIR) :
	make -C $(LIB_DIR)

clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJS)

fclean: clean 
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: $(LIB_DIR) clean
