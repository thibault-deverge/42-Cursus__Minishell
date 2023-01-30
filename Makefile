####################
## VARIABLES

NAME	= minishell
CFLAGS	= -Wall -Wextra -Werror -I$(INCDIR) -Ilibft -g
CC	= clang
LIBFT = ./libft/libft.a
INCDIR	= includes

####################
## SOURCES

SRCS =	./main.c \
		./sources/prompt/prompt.c \
		./sources/display/print.c \
		./sources/parsing/pop/pre_parsing.c \
		./sources/parsing/pop/pre_parsing_utils.c \
		./sources/parsing/env/init_env.c \
		./sources/parsing/tibo/parse_commands.c \
		./sources/parsing/tibo/check_type.c \
		./sources/parsing/tibo/commands.c \
		./sources/parsing/tibo/redirections.c \
		./sources/helpers/environment.c \
		./sources/helpers/matrice.c \
		./sources/helpers/errors.c \
		./sources/helpers/free.c \

OBJS	= $(SRCS:.c=.o)

####################
## RULES

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
