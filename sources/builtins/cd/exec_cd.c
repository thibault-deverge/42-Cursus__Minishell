#include "minishell.h"

int	exec_cd(t_command *command, t_env *env)
{
	t_variable	*old_pwd;
	t_variable	*pwd;

	if (command->cmd[2])
		return (print_error(ERROR_CD));
	old_pwd = get_variable(env, "OLDPWD", 6);
	old_pwd->content = get_var_content(env, "PWD");
	if (chdir(command->cmd[1]))
	{

	}
}
