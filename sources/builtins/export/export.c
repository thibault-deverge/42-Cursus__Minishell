#include "minishell.h"

static int	check_var_content(char *var)
{
	
}

static void	manage_variable(char *new_var, t_env *env)
{
	
}

void	export(t_command *command, t_env *env)
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
