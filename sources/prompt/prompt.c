#include "minishell.h"

/*
 * @summary:
 * 		- Ask user to enter a prompt and return it.
 * 		- Return NULL if user enter EOF.
*/
char	*get_prompt(void)
{
	char	*command;

	command = readline("$> ");
	if (!command)
	{
		rl_clear_history();
		return (NULL);
	}
	add_history(command);
	return (command);
}
