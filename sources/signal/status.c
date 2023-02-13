/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 03:18:07 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 03:19:09 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Update global error variable depend the result of function
 * 		WIFEXITED and WIFSIGNALED.
*/
void	status_code(int status)
{
	if (WIFEXITED(status))
		g_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_value = WTERMSIG(status);
}
