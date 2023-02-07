#ifndef MINISHELL_H
# define MINISHELL_H

/*******************************************************/
/*                        INCLUDES                     */
/*******************************************************/

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>

/*******************************************************/
/*                         DEFINES                     */
/*******************************************************/

# define ERROR_PROMPT	"exit\n"
# define ERROR_SYNTAX	"error: syntax error near redirection\n"
# define ERROR_QUOTES	"error: missing terminating quote character\n"
# define INVALID_KEY	"not a valid identifier\n"
# define ERROR_ENV		"env: too many arguments\n"
# define ERROR_CD_ARG	"cd: too many arguments\n"
# define ERROR_CD_FILE  "cd: no such file or directory\n"
# define ERROR_CD_HOME  "cd: home directory can't be found\n"
# define ERROR_EXIT_ARG "exit\nexit: too many arguments\n"
# define ERROR_EXIT_NUM "exit\nexit: numeric argument required\n"
# define ERROR_OPEN_FD	"No such file or directory\n"
# define ERROR_CMD_LOST "error: No such file or directory\n"
# define ERROR_TEST		"error: command not found\n"

# define EXIT_PROMPT	1
# define EXIT_ALLOC		2
# define EXIT_PARSE_CMD 3
# define EXIT_CMD		4
# define EXIT_BUILTIN	5

# define COMMAND		0
# define REDI			1
# define SPACEBAR		2
# define PIPE			3

# define FIRST_CMD		1
# define MIDDLE_CMD		2
# define LAST_CMD		3

# define PATH_SIZE		1024

# define IN				1
# define OUT			2
# define ADD_OUT		3
# define NO_FILE		-1

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
	int					fds[2];
	int					index;
	struct s_command	*next;
}			t_command;

typedef struct s_list
{
	pid_t		*pid;
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
	int		(*f)(t_command *command, t_env *env);
}			t_builtins;

/* *******************************************	*/
/*					PARSING						*/
/* *******************************************	*/
/*					main_parsing				*/
t_list		*main_parsing(t_list *lst, char *cmd, t_env *env);
/*					prompt						*/
char		*get_input(void);
/*					environment					*/
void		get_env(t_env *env, char **envp);
t_env		*add_variable(t_env *envp, char *str);
void		init_ascii_index(t_env *envp);
t_env		*insert_var_node(t_env *env, char *str);
char		*get_var_content(t_env *env, char *var_name);
t_variable	*set_var_content(t_variable *var, char *str);
t_variable	*get_variable(t_env *env, char *var_name, int len);
/*					pre_parsing					*/
t_parse		*pre_parse(t_parse *parse, char *cmd, t_env *env);
int			manage_arg(char *cmd, t_parse *parse, int len, t_env *env);
void		define_rule_arg(t_parse *parse, int rule);
int			check_arg(char c);
t_parse		*add_new_token(char *arg, int start, int len, t_parse *parse);
char		*get_value_of_key(char *key, int len, t_env *env);
/*					parse_command				*/
t_list		*parse_commands(t_list *list_commands, t_parse *list_tokens);
t_command	*initialize_command(void);
int			handle_redirection(t_command *command, t_token *token);
int			handle_command(t_command *command, t_token *token);
int			is_empty_command(t_command *command);
int			is_redirection_invalid(char c);
int			is_command(t_token *token);

/* *******************************************	*/
/*					BUILT-IN					*/
/* *******************************************	*/
/*					echo						*/
int			exec_echo(t_command *command, t_env *env);
/*					pwd							*/
int			exec_pwd(t_command *command, t_env *env);
/*					cd							*/
int			exec_cd(t_command *command, t_env *env);
/*			     	export						*/
int			exec_export(t_command *command, t_env *env);
int			get_key_len(char *var);
t_variable	*manage_key(char *new_var, int key_len, t_env *env);
char		*set_new_content(t_variable *var, char *value);
int			add_new_content(t_variable *var, char *value);
t_variable	*add_new_variable(char *var, int len, t_env *env);
void		manage_variable(char *new_var, t_env *env);
t_variable	*get_last_var(t_env *env);
int			check_key_name(char *key, int len, char *built);
/*					env							*/
int			exec_env(t_command *command, t_env *env);		
/*					unset						*/
int			exec_unset(t_command *command, t_env *env);
/*					exit						*/
int			exec_exit(t_command *command, t_env *env);

/* *******************************************	*/
/*					EXECUTION					*/
/* *******************************************	*/
/*					main_execution				*/
t_list		*main_execution(t_list *lst, t_env *env);
/*					builtins					*/
int			check_builtins(t_command *command, t_env *env);
/*				convert_env						*/
char		**convert_env(t_env *env);
/*				pipex							*/
int			pipex(t_list *list_commands, t_env *env);
int			exec_command(char **command, char *paths, char **env);
/*				fork							*/
int			first_cmd(t_list *list_cmd, int pipes[][2], t_env *env);
int			last_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env);
int			middle_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env);
int			single_cmd(t_list *lst, t_command *cmd, t_env *env);
/*				close							*/
void		close_files(t_command *command);
void		close_pipes(int pipes[][2]);
void		close_pipe(int *pipe);
/*				utils							*/
int			is_last_command(t_command *command);
int			make_dup_cmd(int pipes[][2], int idx_cmd);
void		exit_child(t_list *list_cmd, t_env *env, int is_perror);
char		*ft_joinpath(char const *s1, char const *s2);
int			restore_fd(t_command *command, int fdin, int fdout);
/*					heredoc						*/
int			heredoc_manager(t_list *lst);
/*				    redirections					*/
void		redi_manager(t_command *command);

/* *******************************************	*/
/*					UTILS						*/
/* *******************************************	*/
/*					insert_matrice.c			*/
char		**insert_matrix(char **matrice, char *str);
char		*ft_sepjoin(const char *s1, const char *s2, char c);

/* *******************************************	*/
/*					HELPERS						*/
/* *******************************************	*/
/*					free.c						*/
void		free_all(t_variable *var, t_command *cmd, t_token *tok);
void		free_env(t_variable *var);
void		free_commands(t_command *command);
void		free_tokens(t_token *token);
void		free_matrix(char **matrice);
void		free_matrices(char **matrix1, char **matrix2);
/*					errors.c					*/
void		throw_perror(int exit_value);
int			print_complete_error(char *err_src, char *err_sub, int len_sub, char *err_msg);
int			print_error(char *err_msg);
int			print_perror(void);
/*					display.c					*/
void		print_env(t_env *env);
void		print_export(t_env *env);
/*					test.c						*/
void		print_cmd(t_list *list_commands);

#endif
