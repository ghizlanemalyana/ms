CFLAGS = -Wall -Wextra -Werror
SOURCES = $(shell find src/ -type f -name "*.c")
OBJS = $(SOURCES:.c=.o)
LIB_DIR = libft/
LIBFT = $(LIB_DIR)libft.a
NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc -g -fsanitize=address $(OBJS) $(LIBFT) -lreadline -o $(NAME)

%.o : %.c minishell.h
	cc -g -fsanitize=address $(flags) -c $< -o $@

$(LIBFT) :
	make -C $(LIB_DIR)

clean:
	make clean -C $(LIB_DIR)
	rm -f $(OBJS)

fclean: clean 
	make fclean -C $(LIB_DIR)
	rm -f $(NAME)

re: fclean all


