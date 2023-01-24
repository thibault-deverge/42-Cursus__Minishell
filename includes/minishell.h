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
typedef struct s_token
{
	char			*arg;
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

/*******************************************************/
/*                       PROTOTYPES                    */
/*******************************************************/
/*                        PARSING                      */

t_list	*parse(t_list *lst, char *cmd, t_env *env);
t_list	*get_commands(t_parse *parse);

/*                       EXECUTION                     */

/*                       BUILT-INS                     */

/*			  			   echo         	           */

/*			    		    cd          	           */

/*			   			   pwd         	               */

/*			              export		               */
void	export(char *cmd, t_env *envp);

/*			              unset             	       */

/*	              		   env			               */
void	get_env(t_env *env, char **envp);
t_env	*add_variable(t_env *envp, char *str);
void	init_ascii_index(t_env *envp);

/*           			  exit		                   */

/*                       DISPLAY                       */

void	print_envp(t_env *envp);
void	print_export(t_env *envp);

/*						PROMPT							*/
char	*get_input(t_env *env);
char	*get_prompt(t_env *env);
char	*get_var_content(t_env *env, char *var_name);

/*						HELPERS							*/
void	free_env(t_variable *var);

#endif
