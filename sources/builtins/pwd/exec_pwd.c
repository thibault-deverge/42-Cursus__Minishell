#include "minishell.h"

/*
 * @summary:
 * 		- Get length of PWD and alloc dynamically a string of its size.
 * 		- Copy pwd in this string and print it then free it.
*/
int	exec_pwd(t_command *command, t_env *env)
{
	char	*pwd_buf;
	int		pwd_len;

	(void)*command;
	pwd_len = ft_strlen(get_var_content(env, "PWD"));
	pwd_buf = malloc(sizeof(char) * (pwd_len + 1));
	if (!pwd_buf)
		return (print_perror());
	pwd_buf = getcwd(pwd_buf, pwd_len + 1);
	ft_putstr_fd(pwd_buf, 1);
	ft_putchar_fd('\n', 2);
	free(pwd_buf);
	return (1);
}
