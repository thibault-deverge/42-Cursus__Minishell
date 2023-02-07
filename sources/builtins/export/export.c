#include "minishell.h"

int	exec_export(t_command *command, t_env *env)
{
	int	i;

	i = 1;
	if (!command->cmd[i])
	{
		print_export(env);
		return (RETURN_SUCCESS);
	}
	while (command->cmd[i])
	{
		if (!manage_variable(command->cmd[i], env))
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}
