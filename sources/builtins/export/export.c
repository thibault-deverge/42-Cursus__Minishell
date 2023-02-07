#include "minishell.h"

/*
 * @summary:
 * 		- Loop through the environment linked list and print all variable
 * 		as the command 'export' would do using ASCII order.
*/
static void	print_export(t_env *env)
{
	int			index;
	t_variable	*tmp;

	index = 0;
	tmp = env->var;
	while (tmp)
	{
		if (index == tmp->index)
		{
			if (tmp->content && ft_strcmp(tmp->name, "_") != 0)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
			else if (!tmp->content && ft_strcmp(tmp->name, " ") != 0)
				printf("declare -x %s\n", tmp->name);
			tmp = env->var;
			index++;
		}
		else
			tmp = tmp->next;
	}
}

/*
 * @summary:
 * 		- Print environment by ASCII order if no arguments are passed.
 * 		- Export variable passed as parameters if arguments are passed
 * 		to the built-in.
*/
int	exec_export(t_command *command, t_env *env)
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
