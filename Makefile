NAME	= minishell

CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR) -g

CC	= clang

SRCS =	./main.c \
		./parsing/init_env.c \

INCDIR	= includes

OBJS	= $(SRCS:.c=.o)

%.o:%.c
		$(CC) -c $< -o $@ $(CFLAGS)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
