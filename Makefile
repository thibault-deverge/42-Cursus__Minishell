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
		./sources/parsing/environment/get_environment.c \
		./sources/parsing/pre_parsing/pre_parsing.c \
		./sources/parsing/pre_parsing/argument_manager.c \
		./sources/parsing/pre_parsing/utils.c \
		./sources/parsing/parsing_commands/parse_commands.c \
		./sources/parsing/parsing_commands/redirections.c \
		./sources/parsing/parsing_commands/utils.c \
		./sources/builtins/echo/echo.c \
		./sources/builtins/pwd/pwd.c \
		./sources/builtins/env/env.c \
		./sources/builtins/unset/unset.c \
		./sources/builtins/cd/cd.c \
		./sources/builtins/exit/exit.c \
		./sources/builtins/export/export.c \
		./sources/builtins/export/key.c \
	    ./sources/execution/main_execution.c \
		./sources/execution/builtins/builtins.c \
		./sources/execution/redirections/heredoc_manager.c \
		./sources/execution/redirections/heredoc_signal.c \
		./sources/execution/redirections/redi_manager.c \
		./sources/execution/pipex/pipex.c \
		./sources/execution/pipex/single_cmd.c \
		./sources/execution/pipex/fork_pipex.c \
		./sources/execution/pipex/close_pipex.c \
		./sources/execution/pipex/utils_pipex.c \
		./sources/signal/signal.c \
		./sources/signal/status.c \
    	./sources/utils/insert_matrix.c \
		./sources/utils/ft_sepjoin.c \
		./sources/utils/environment/convert_environment.c \
		./sources/utils/environment/add_variable.c \
		./sources/utils/environment/modify_content.c \
		./sources/utils/environment/ascii.c \
		./sources/utils/environment/getter.c \
		./sources/utils/command/initialize_command.c \
		./sources/utils/ft_atoll.c \
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
