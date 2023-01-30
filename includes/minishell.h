#ifndef MINISHELL_H
# define MINISHELL_H

/*******************************************************/
/*                        INCLUDES                     */
/*******************************************************/

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>

/*******************************************************/
/*                         DEFINES                     */
/*******************************************************/

# define ERROR_PROMPT	"\nExit minishell - prompt receive NULL\n"
# define ERROR_SYNTAX	"syntax error near redirection\n"

# define EXIT_PROMPT	1
# define EXIT_ALLOC		2
# define EXIT_PARSE_CMD 3

# define COMMAND		1
# define REDI			0

/*******************************************************/
/*                       STRUCTURES                    */
/*******************************************************/

/*linked list that contains the env                    */
/*the index corresponds to the ascii order             */
typedef struct s_variable
{
	char				*name;
	char				*content;
	int					index;
	struct s_variable	*next;
}						t_variable;

typedef struct s_env
{
	t_variable	*var;
}				t_env;

/*linked list that contains the commands               */
typedef struct s_command
{
	char				**cmd;
	char				**redi;
	struct s_command	*next;
}			t_command;

typedef struct s_list
{
	size_t		nb_cmd;
	t_command	*first;
}				t_list;

/*linked list to parse the args						   */
/*the index corresponds to the order of the linked list*/
/*the rule that contains if the arg is COMMAND or REDI */
typedef struct s_token
{
	char			*arg;
	int				index;
	int				rule;
	struct s_token	*next;
}					t_token;

typedef struct s_parse
{
	t_token	*token;
}			t_parse;

/*singleton of builtins								   */
typedef struct s_builtins
{
	char	*name;
//	void	(f*)(t_command *command, t_env *envp); 
}			t_builtins;

/* *******************************************	*/
/*					PARSING						*/
/* *******************************************	*/
/*					main_parsing				*/
t_list		*main_parsing(t_list *lst, char *cmd, t_env *env);
/*					prompt						*/
char		*get_input(t_env *env);
/*					environment					*/
void		get_env(t_env *env, char **envp);
t_env		*add_variable(t_env *envp, char *str);
void		init_ascii_index(t_env *envp);
t_env		*insert_var_node(t_env *env, char *str);
char		*get_var_content(t_env *env, char *var_name);
t_variable	*set_var_content(t_variable *var, char *str);
/*					pre_parsing					*/
t_parse		*pre_parse(t_parse *parse, char *cmd, t_env *env);
void		define_rule_arg(t_parse *parse, int rule);
int			check_arg(char c);
t_parse		*add_new_token(char *arg, int start, int len, t_parse *parse);
char		*get_value_of_key(char *key, int len, t_env *env);
/*					parse_command				*/
t_list		*parse_commands(t_list *list_commands, t_parse *list_tokens);
t_command	*initialize_command(void);
int			handle_redirection(t_command *command, t_token *token);
int			handle_command(t_command *command, t_token *token);
int			is_redirection_invalid(char c);
int			is_redirection(char *token);
int			is_command(t_token *token);
int			is_pipe(char *token);

/* *******************************************	*/
/*					BUILT-IN					*/
/* *******************************************	*/

/* *******************************************	*/
/*					EXECUTION					*/
/* *******************************************	*/

/* *******************************************	*/
/*					UTILS						*/
/* *******************************************	*/
/*					insert_matrice.c			*/
char		**insert_matrice(char **matrice, char *str);

/* *******************************************	*/
/*					HELPERS						*/
/* *******************************************	*/
/*					free.c						*/
void		free_all(t_variable *var, t_command *cmd, t_token *tok);
void		free_env(t_variable *var);
void		free_commands(t_command *command);
void		free_tokens(t_token *token);
void		free_matrice(char **matrice);
/*					errors.c					*/
void		throw_error(char *err_msg, int exit_value);
void		throw_perror(int exit_value);
int			print_error(char *err_msg);
int			print_perror(void);
/*					display.c					*/
void		print_envp(t_env *envp);
void		print_export(t_env *envp);

#endif
