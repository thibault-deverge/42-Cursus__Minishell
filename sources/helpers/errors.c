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
	if (!lstat(err_src, &buf))
	{
		ft_putstr_fd("is a directory\n", 2);
		return (126);
	}
	ft_putstr_fd(err_msg, 2);
	return (127);
}

/*
 * @summary:
 * 		- Use perror() system call to display and error with ERRNO'
 * 		and return NULL.
*/
int	print_perror(void)
{
	perror("error");
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
