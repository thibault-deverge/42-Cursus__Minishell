#include "minishell.h"

int	single_cmd(t_list *lst, t_command *cmd, t_env *env)
{
	char		*paths;
	pid_t		pid;
	int			status;
	int			exit_value;

	if (!lst->first->cmd)
		return (0);
	pid = fork();
	if (pid == -1)
		return (print_perror());
	if (pid == 0)
	{
		if (!redi_manager(cmd))
			return (RETURN_FAILURE);
		env->envp = convert_env(env);
		if (!env->envp)
			exit_child(lst, env, 1, 1);
		paths = get_var_content(env, "PATH");
		exit_value = exec_command(cmd->cmd, paths, env->envp);
		exit_child(lst, env, 0, exit_value);
	}
	waitpid(pid, &status, 0);
	status_code(status);
	return (RETURN_FAILURE);
}
