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
	t_variable	*variable;
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
	t_command	*cmd;
}				t_list;

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

/*                       EXECUTION                     */

/*                       BUILT-INS                     */

/*			  			   echo         	           */

/*			    		    cd          	           */

/*			   			   pwd         	               */

/*			              export		               */
void	export(char *cmd, t_env *envp);

/*			              unset             	       */

/*	              		   env			               */
void	get_envp(t_env *envp, char **env);
t_env	*add_variable(t_env *envp, char *str);
void	init_ascii_index(t_env *envp);

/*           			  exit		                   */

/*                       DISPLAY                       */

void	print_envp(t_env *envp);
void	print_export(t_env *envp);

#endif
