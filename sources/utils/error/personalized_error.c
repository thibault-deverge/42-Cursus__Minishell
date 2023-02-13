/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   personalized_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 00:51:28 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 00:56:55 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Print an error personalized depend the source of it. Receive both
 * 		sources and messages as parameters.
 * 		- Error source will depend of the return value of the lstat syscall.
 * 		- Return global error variable.
*/
int	print_perso_error(char *err_src, char *err_msg)
{
	struct stat	buf;

	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": ", 2);
	if (!lstat(err_src, &buf)
		&& (!ft_strncmp(err_src, "./", 2) || err_src[0] == '/'))
	{
		if (S_ISDIR(buf.st_mode))
			ft_putstr_fd(ERROR_DIR, 2);
		else if (access(err_src, X_OK))
			ft_putstr_fd(ERROR_PERM, 2);
		else
			ft_putstr_fd(ERROR_OPEN_FD, 2);
		g_value = 126;
		return (g_value);
	}
	else if (ft_strncmp(err_src, "./", 2) == 0 || err_src[0] == '/')
		ft_putstr_fd(ERROR_OPEN_FD, 2);
	else
		ft_putstr_fd(err_msg, 2);
	g_value = 127;
	return (g_value);
}
