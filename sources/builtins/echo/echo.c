#include "minishell.h"

/*
 * @summary:
 * 		- Check if string passed as parameter is flag '-n'
 * 		- Also valid with x number of 'n' after the '-' while
 * 		there is no other characters than these ones.
*/
int	check_option_echo(char *flag)
{
	int	i;

	i = 2;
	if (ft_strncmp(flag, "-n", 2))
		return (0);
	else
	{
		while (flag[i])
		{
			if (flag[i] != 'n')
				return (0);
			i++;
		}
	}
	return (1);
}

/*
 * @summary:
 * 		- Reproduce behavior of command 'echo' and its flag '-n'
 * 		- Loop through first args to check if the option '-n' was passed
 * 		and don't print if it a valid flag.
 * 		- Print the other args with a space characher in between.
 * 		- End with a '\n' or not depend if flag '-n' were present.
*/
void	exec_echo(t_command *command, t_env env)
{
	char	**cmd_args;
	int		is_option;
	int		i;

	i = 1;
	is_option = 0;
	cmd_args = command->cmd;
	while (check_option_echo(cmd_args[i]))
	{
		is_option = 1;
		i++;
	}
	while (cmd_args[i])
	{
		ft_putstr_fd(cmd_args[i], 1);
		ft_putchar_fd(' ', 1);
	}
	if (!is_option)
		ft_putchar_fd('\n', 1);
}
