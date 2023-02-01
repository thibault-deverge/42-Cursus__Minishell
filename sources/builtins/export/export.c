#include "minishell.h"

void	export(char **command, t_env *env)
{
	int	i;

	i = 1;
	if (!command[i])
	{
		print_export(env);
		return ;
	}
	while (command[i])
	{
		manage_variable(command[i], env);
		i++;
	}
}
