#include "minishell.h"

/*
 * @summary:
 * 		- Split the paths as parameter to have a matrix of paths.
 * 		- Check if command typed by the user is full path and 
 * 		execute it if its the case.
 * 		- Try name of the command with every path given and execute 
 * 		once the valid path was found.
*/
int	exec_command(char **command, char *paths, char **env)
{
	char	**paths_split;
	char	*command_path;
	int		i;

	i = 0;
	paths_split = NULL;
	if (paths)
	{
		paths_split = ft_split(paths, ':');
		if (!paths_split)
			return (print_perror());
	}
	if (!access(command[0], F_OK))
		execve(command[0], command, env);
	while (paths_split && paths_split[i])
	{
		command_path = ft_joinpath(paths_split[i], command[0]);
		if (!access(command_path, F_OK))
			execve(command_path, command, env);
		free(command_path);
		i++;
	}
	free_matrices(env, paths_split);
	return (print_error(ERROR_CMD_LOST));
}

/*
 * @summary:
 * 		- Make a fork and get path in the environment.
 * 		- Dup fds of pipe passed as parameter for stdout and close
 * 		them all unless the standards ones.
 * 		- Check if it's necessary to redirect into files and close
 * 		the one used.
 * 		- Execute the command and exit the fork.
*/
int	first_cmd(t_list *list_cmd, int pipes[][2], t_env *env)
{
	char	**envp;
	char	*paths;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_perror());
	if (pid == 0)
	{
		paths = get_var_content(env, "PATH");
		envp = convert_env(env);
		if (!envp)
			return (print_perror());
		if (!make_dup_cmd(pipes, FIRST_CMD))
			exit_child(list_cmd, env, 1);
		redi_manager(list_cmd->first);
		close_files(list_cmd->first);
		if (check_builtins(list_cmd->first, env) == 0)
			exec_command(list_cmd->first->cmd, paths, envp);
		exit_child(list_cmd, env, 0);
	}
	close(pipes[0][1]);
	return (1);
}

int	last_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env)
{
	char	**envp;
	char	*paths;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_perror());
	if (pid == 0)
	{
		paths = get_var_content(env, "PATH");
		envp = convert_env(env);
		if (!envp)
			return (print_perror());
		if (!make_dup_cmd(pipes, LAST_CMD))
			exit_child(lst, env, 1);
		redi_manager(cmd);
		close_files(cmd);
		if (check_builtins(cmd, env) == 0)
			exec_command(cmd->cmd, paths, envp);
		exit_child(lst, env, 0);
	}
	close(pipes[0][0]);
	return (pid);
}

int	middle_cmd(t_list *lst, t_command *cmd, int pipes[][2], t_env *env)
{
	char	**envp;
	char	*paths;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_perror());
	if (pid == 0)
	{
		paths = get_var_content(env, "PATH");
		envp = convert_env(env);
		if (!envp)
			return (print_perror());
		if (!make_dup_cmd(pipes, MIDDLE_CMD))
			exit_child(lst, env, 1);
		redi_manager(cmd);
		close_files(cmd);
		if (check_builtins(cmd, env) == 0)
			exec_command(cmd->cmd, paths, convert_env(env));
		exit_child(lst, env, 0);
	}
	close(pipes[0][0]);
	close(pipes[1][1]);
	return (pid);
}
