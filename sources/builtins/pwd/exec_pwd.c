#include "minishell.h"

/*
 * @summary:
 * 		- Copy pwd in 'pwd_buf' and print it.
*/
int	exec_pwd(t_command *command, t_env *env)
{
	char	pwd_buf[PATH_SIZE];

	(void)*command;
	(void)*env;
	if (!getcwd(pwd_buf, PATH_SIZE))
		return (print_perror());
	ft_putstr_fd(pwd_buf, 1);
	ft_putchar_fd('\n', 2);
	return (RETURN_SUCCESS);
}
