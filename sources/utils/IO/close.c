/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 02:37:31 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 02:37:47 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check if files are open and close them if they are.
*/
void	close_files(t_command *command)
{
	if (command->fds[0] != -1)
		close(command->fds[0]);
	if (command->fds[1] != -1)
		close(command->fds[1]);
}

/*
 * @summary:
 * 		- Close pipe passed as parameter.
*/
void	close_pipe(int *pipe)
{
	close(pipe[0]);
	close(pipe[1]);
}