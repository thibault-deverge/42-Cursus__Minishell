#include "minishell.h"

/*
 * @summary:
 * 		- Free command & end linked list before exiting the process.
*/
static void	free_exit(t_command *command, t_env *env)
{
	free_commands(command);
	free_env(env->var);
	exit(1);
}

/*
 * @summary:
 * 		- Receive a string as parameter and check if every characters
 * 		is a digit.
*/
static int	is_number(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
 * @summary:
 * 		- If no argument for exit, free & exit with a status of 1. 
 * 		- If first argument is not a digit, print error, free and exit
 * 		with status of 1.
 * 		- If more than two arguments, print error and return 0 without freeing.
 * 		- If argument is valid, modulo argument by 256 and and exit 
 * 		with this status.
 *
*/
int	exec_exit(t_command *command, t_env *env)
{
	int	exit_status;

	if (!command->cmd[1])
	{
		free_exit(command, env);
		exit(1);
	}
	else
	{
		if (!is_number(command->cmd[1]))
		{
			print_error(ERROR_EXIT_NUM);
			free_exit(command, env);
			exit(1);
		}
		if (command->cmd[2])
		{
			print_error(ERROR_EXIT_ARG);
			return (0);
		}
		exit_status = ft_atoi(command->cmd[1]);
		free_exit(command, env);
		exit(exit_status % 256);
	}
	return (0);
}
