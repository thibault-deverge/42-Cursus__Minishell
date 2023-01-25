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
 * 
*/
void	throw_perror(int exit_value)
{
	perror("error:");
	exit(exit_value);
}
