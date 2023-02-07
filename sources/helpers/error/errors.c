#include "minishell.h"

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

/*
 * @summary:
 * 		- Print complete error in the form :
 * 		"<err_src>: '<err_sub>': <err_msg>"
*/
int	print_complete_error(char *err_src, char *err_sub, int len_sub, char *err_msg)
{
	int	i;

	i = 0;
	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": \'", 2);
	while (i < len_sub)
	{
		ft_putchar_fd(err_sub[i], 2);
		i++;
	}
	ft_putstr_fd("\': ", 2);
	ft_putstr_fd(err_msg, 2);
	return (0);
}

int	print_perso_error(char *err_src, char *err_msg)
{
	ft_putstr_fd(err_src, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err_msg, 2);
	return (RETURN_FAILURE);
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
