#include "minishell.h"

/*
 * @summary:
 * 		- Run only when there are multiples commands and will handle
 * 		each commands separately in a fork. 
*/
int	pipex(t_list *list_commands, t_env *env)
{
	t_command	*command;
	int			pipes[2][2];
	pid_t		pid;

	command = list_commands->first;
	if (pipe(pipes[0]) == -1)
		return (print_perror());
	if (!handle_first_cmd(list_commands, pipes, env))
		return (0);
	command = command->next;
	while (command)
	{
		if (pipe(pipes[1]) == -1)
			return (print_perror());
		pid = handle_cmd(list_commands, command, pipes, env);
		if (pid == 0)
			return (0);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		command = command->next;
	}
	waitpid(pid, NULL, 0);
	return (1);
}
