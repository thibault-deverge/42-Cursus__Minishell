#ifndef MINISHELL_H
# define MINISHELL_H

/*******************************************************/
/*                        INCLUDES                     */
/*******************************************************/

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
//# include <readline/readline.h>
//# include <readline/history.h>

/*******************************************************/
/*                         DEFINES                     */
/*******************************************************/

/*******************************************************/
/*                       STRUCTURES                    */
/*******************************************************/

/*linked list that contains the env                    */
/*the index corresponds to the ascii order             */
typedef struct s_env
{
	char			*name;
	char			*content;
	int			index;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_env	*envp;
}			t_data;

/*******************************************************/
/*                       PROTOTYPES                    */
/*******************************************************/

/*                        PARSING                      */

/*                       EXECUTION                     */

/*                       BUILT-IN                      */

/*			   echo         	       */

/*			    cd          	       */

/*			    pwd         	       */

/*			   export		       */
void	export(char *cmd, bool pipe, t_data *data);

/*			   unset         	       */

/*			    env			       */
void	get_envp(t_data *data, char **env);
t_data	*add_env(t_data *data, char *str);
void	init_ascii_index(t_data *data);

/*			    exit		       */

/*                        DISPLAY                      */

void	print_envp(t_data *data);
void	print_export(t_data *data);

#endif
