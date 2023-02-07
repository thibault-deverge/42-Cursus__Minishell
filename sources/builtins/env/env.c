#include "minishell.h"

/*
 * @summary:
 * 		- Loop through the 'env' linked list and print every variables.
*/
static void	print_env(t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

/*
 * @summary:
 * 		- Check if there is no argument to built-in env and print
 * 		the environment if there is not.
*/
int	exec_env(t_command *command, t_env *env)
{
	if (command->cmd[1])
		print_error(ERROR_ENV);
	else
		print_env(env);
	return (0);
}
