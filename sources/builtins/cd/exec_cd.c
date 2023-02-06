#include "minishell.h"

/*
 * @summary:
 *		- Modify content of variable "name" passed as parameter
 *		with the value of parameter "content".
 *		- Check if content exists because it is allocated dynamically
 *		with ft_strdup() when the function is called.
*/
static int	modify_var_content(t_env *env, char *name, char *content)
{
	t_variable	*tmp_var;

	tmp_var = env->var;
	if (!content)
		return (-1);
	while (tmp_var)
	{
		if (!ft_strcmp(tmp_var->name, name))
		{
			tmp_var->content = content;
			return (0);
		}
		tmp_var = tmp_var->next;
	}
	free(content);
	return (0);
}

/*
 * @summary:
 * 		- Get content of the variable HOME and throw error if
 * 		it doesn't exists.
 * 		- Get back to home directory and update PWD variable.
*/
static int	cd_to_home(t_env *env)
{
	char	pwd[1024];
	char	*home;

	home = get_var_content(env, "HOME");
	if (!home)
		return (print_error(ERROR_CD_HOME));
	if (chdir(home) == -1)
		return (print_error(ERROR_CD_FILE));
	if (!getcwd(pwd, 1024))
		return (print_perror());
	if (modify_var_content(env, "PWD", ft_strdup(pwd)) == -1)
		return (print_perror());
	return (1);
}

/*
 * @summary:
 * 		- Set OLDPWD with PWD variable.
 * 		- Check if args are empty and bring back to home if it's the case.
 * 		- Check if there is more than one argument and throw error.
 * 		- Change directory to the arg 1 and get the current location
 * 		to update PWD variable.
*/
int	exec_cd(t_command *command, t_env *env)
{
	char	old_pwd[1024];
	char	pwd[1024];

	if (!getcwd(old_pwd, 1024))
		return (print_perror());
	if (modify_var_content(env, "OLDPWD", ft_strdup(old_pwd)) == -1)
		return (print_perror());
	if (!command->cmd[1])
		return (cd_to_home(env));
	else
	{
		if (command->cmd[2])
			return (print_error(ERROR_CD_ARG));
		if (chdir(command->cmd[1]))
			return (print_error(ERROR_CD_FILE));
		if (!getcwd(pwd, 1024))
			return (print_perror());
		if (modify_var_content(env, "PWD", ft_strdup(pwd)) == -1)
			return (print_perror());
	}
	return (1);
}
