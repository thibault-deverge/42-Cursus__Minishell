/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 21:42:59 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/15 11:16:58 by pmieuzet         ###   ########.fr       */
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

/*
 * @summary:
 * 		- Loop through first args to check if the option '-n' was passed
 * 		and don't print if it a valid flag.
 * 		- Print the other args with a space characher in between.
 * 		- End with a '\n' or not depend if flag '-n' were present.
*/
int	exec_echo(t_command *command, t_env *env)
{
	char	**cmd_args;
	int		is_option;
	int		i;

	i = 1;
	is_option = 0;
	cmd_args = command->cmd;
	(void)*env;
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
	return (RETURN_SUCCESS);
}
