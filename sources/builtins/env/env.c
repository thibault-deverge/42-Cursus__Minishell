#include "minishell.h"

int exec_env(t_command *command, t_env *env)
{
	if (command->cmd[1])
		return(print_error(ERROR_ENV));
	else
		print_env(env);
	return (RETURN_SUCCESS);
}
