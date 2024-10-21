CFLAGS = -Wall -Wextra -Werror
SOURCES = $(shell find src/ -type f -name "*.c")
OBJS = $(SOURCES:.c=.o)
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a
NAME = minishell

all: $(NAME) clean //! Remove clean dependency later

$(NAME): $(OBJS) $(LIBFT)
	cc $(OBJS) $(LIBFT) -lreadline -L /Users/gmalyana/.brew/opt/readline/lib -o $(NAME)

%.o : %.c minishell.h
	cc -I /Users/gmalyana/.brew/opt/readline/include -c $< -o $@ 

$(LIBFT) :
	make -C $(LIB_DIR)

clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJS)

fclean: clean 
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)

re: fclean all


