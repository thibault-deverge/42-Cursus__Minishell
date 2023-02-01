#include "minishell.h"

/*
 * @summary:
 * 		- Display error message passed as parameter on STDERR
 * 		and exit with integer passed as 'exit value'.
*/
void	throw_error(char *err_msg, int exit_value)
{
	ft_putstr_fd(err_msg, 2);
	exit(exit_value);
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

/*
 * @summary:
 * 		- Print string passed as parameter as an error message
 * 		and return NULL;
*/
int	print_error(char *err_msg)
{
	ft_putstr_fd(err_msg, 2);
	return (0);
}

int	print_complete_error(char *err_src, char *err_sub, int len_sub, char *err_msg)
{
	int	i;

	i = 0;
	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(" \'", 2);
	while (i < len_sub)
	{
		ft_putchar_fd(err_sub[i], 2);
		i++;
	}
	ft_putstr_fd("\': ", 2);
	ft_putstr_fd(err_msg, 2);
	return (0);
}

/*
 * @summary:
 * 		- Use perror() system call to display and error with ERRNO'
 * 		and return NULL.
*/
int	print_perror(void)
{
	perror("error");
	return (0);
}