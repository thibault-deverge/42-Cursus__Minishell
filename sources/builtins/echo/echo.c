/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:42:59 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 14:32:07 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check if string passed as parameter is flag '-n'
 * 		- Also valid with x number of 'n' after the '-' while
 * 		there is no other characters than these ones.
*/
static int	check_option_echo(char *flag)
{
	int	i;

	i = 2;
	if (ft_strncmp(flag, "-n", 2))
		return (0);
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static void	echo_in_pipe(t_command *command)
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
	if (cmd_args[i])
		ft_putstr_fd(cmd_args[i++], command->fdout);
	while (cmd_args[i])
	{
		ft_putchar_fd(' ', command->fdout);
		ft_putstr_fd(cmd_args[i], command->fdout);
		i++;
	}
	if (!is_option)
		ft_putchar_fd('\n', command->fdout);
}

static void	echo_std_input(t_command *command)
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
	if (cmd_args[i])
		ft_putstr_fd(cmd_args[i++], 1);
	while (cmd_args[i])
	{
		ft_putchar_fd(' ', 1);
		ft_putstr_fd(cmd_args[i], 1);
		i++;
	}
	if (!is_option)
		ft_putchar_fd('\n', 1);
}

/*
 * @summary:
 * 		- Loop through first args to check if the option '-n' was passed
 * 		and don't print if it a valid flag.
 * 		- Print the other args with a space characher in between.
 * 		- End with a '\n' or not depend if flag '-n' were present.
*/
int	exec_echo(t_command *command, t_env *env)
{
	(void)*env;
	if (command->fdout == 1)
		echo_std_input(command);
	else
		echo_in_pipe(command);
	return (RETURN_SUCCESS);
}
