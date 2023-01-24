NAME	= minishell

CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR) -Ilibft -g

CC	= clang

LIBFT = ./libft/libft.a

SRCS =	./main.c \
		./sources/builtins/init_env.c \
		./sources/builtins/export.c \
		./sources/display/print.c \
		./sources/parsing/parsing.c \
		./sources/parsing/get_commands.c \

INCDIR	= includes

OBJS	= $(SRCS:.c=.o)

%.o:%.c
		$(CC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline
	
clean:
	rm -f $(OBJS)
	make -s -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -s -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
