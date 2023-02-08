#include "minishell.h"

int	restore_fd(t_command *command, int fdin, int fdout)
{
	if (dup2(fdin, 0) < 0)
		return (1);
	close(fdin);
	if (dup2(fdout, 1) < 0)
		return (1);
	close(fdout);
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (command->fds[1] != NO_FILE)
		close(command->fds[1]);
	return (0);
}

int	single_cmd(t_list *lst, t_command *cmd, t_env *env)
{
	char		**envp;
	char		*paths;
	pid_t		pid;
	int 		status;

	pid = fork();
	if (pid == -1)
		return (print_perror());
	if (pid == 0)
	{
		envp = convert_env(env);
		if (!envp)
			exit_child(lst, env, NULL, 1);
		paths = get_var_content(env, "PATH");
		exec_command(cmd->cmd, paths, envp);
		exit_child(lst, env, envp, 0);
	}
	waitpid(pid, &status, 0);
	status_code(status);
	return (0);
}
