NAME	= minishell

CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR) -Ilibft -g

CC	= clang

LIBFT = ./libft/libft.a

SRCS =	./main.c \
		./parsing/init_env.c \

INCDIR	= includes

OBJS	= $(SRCS:.c=.o)

%.o:%.c
		$(CC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	make -s -C ./libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)
	
clean:
	rm -f $(OBJS)
	make -s -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -s -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re
