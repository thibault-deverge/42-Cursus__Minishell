#include "minishell.h"
#include <limits.h>

static int	print_exit(char *value, char *err_msg)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(value, 2);
	ft_putchar_fd(':', 2);
	ft_putstr_fd(err_msg, 2);
	return (0);
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
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
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
*/
int	exec_exit(t_command *command, t_env *env)
{
	long long	exit_status;
	int		limits;

	ft_putstr_fd("exit\n", 1);
	if (!command->cmd[1])
	{
		free_commands(command);
		free_env(env->var);
		exit(g_value);
	}
	else
	{
		if (!is_number(command->cmd[1]))
		{
			print_exit(command->cmd[1], ERROR_EXIT_NUM);
			free_commands(command);
			free_env(env->var);
			g_value = 2;
			exit(g_value);
		}
		if (command->cmd[2])
		{
			print_exit(command->cmd[2], ERROR_EXIT_ARG);
			g_value = 1;
			return (RETURN_FAILURE);
		}
		limits = 0;
		exit_status = ft_atoll(command->cmd[1], &limits);
		free_commands(command);
		free_env(env->var);
		if (limits)
		{
			g_value = 2;
			print_exit(command->cmd[1], ERROR_EXIT_NUM);
			exit(g_value);
		}
		g_value = exit_status % 256;
		exit(g_value);
	}
	return (RETURN_FAILURE);
}
