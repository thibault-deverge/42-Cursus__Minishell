#include "minishell.h"

int	export(t_command *command, t_env *env)
{
	int	i;

	i = 1;
	if (!command->cmd[i])
	{
		print_export(env);
		return (0);
	}
	while (command->cmd[i])
	{
		manage_variable(command->cmd[i], env);
		i++;
	}
	return (0);
}
