#ifndef MINISHELL_H
# define MINISHELL_H

/*******************************************************/
/*                        INCLUDES                     */
/*******************************************************/

# include <stdio.h>
# include <stdlib.h>
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
void	get_envp(t_data *data, char **env);

/*                       EXECUTION                     */

/*                       BUILT-IN                      */

#endif
