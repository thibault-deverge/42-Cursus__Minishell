#include "minishell.h"

/*
 * @summary:
 * 		- Print string passed as parameter as an error message
 * 		and return NULL;
*/
int	print_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (RETURN_FAILURE);
}

int	print_perso_error(char *err_src, char *err_msg)
{
	struct stat	buf;

	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": ", 2);
	if (!lstat(err_src, &buf) && (ft_strncmp(err_src, "./", 2) == 0 || err_src[0] == '/'))
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

/*
 * @summary:
 * 		- Use perror() system call to display and error with ERRNO'
 * 		and return NULL.
*/
int	print_perror(void)
{
	perror("error");
	g_value = 1;
	return (RETURN_FAILURE);
}

/*
 * @summary:
 * 		- Display an error using perror() system call and ERRNO.
 * 		- Exit with the value passed as parameter.
*/
void	throw_perror(int exit_value)
{
	perror("error:");
	exit(exit_value);
}
