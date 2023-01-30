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
		./sources/parsing/main_parsing.c \
		./sources/parsing/prompt/prompt.c \
		./sources/parsing/environment/init_env.c \
		./sources/parsing/environment/environment.c \
		./sources/parsing/pre_parsing/pre_parsing.c \
		./sources/parsing/pre_parsing/pre_parsing_utils.c \
		./sources/parsing/parsing_commands/parse_commands.c \
		./sources/parsing/parsing_commands/check_type.c \
		./sources/parsing/parsing_commands/commands.c \
		./sources/parsing/parsing_commands/redirections.c \
		./sources/utils/insert_matrice.c \
		./sources/helpers/display/print.c \
		./sources/helpers/error/errors.c \
		./sources/helpers/error/free.c \

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
