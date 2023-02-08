#include "minishell.h"

/*
 * @summary:
 * 		- Loop over the pid in the structure 'command' and
 * 		wait for them to finish.
*/
static void	ft_waitpid(t_list *list_commands)
{
	int	i;
	int	status;

	i = 0;
	while (i < list_commands->nb_cmd)
	{
		waitpid(list_commands->pid[i], &status, 0);
		i++;
	}
	status_code(status);
}

/*
 * @summary:
 * 		- Run only when there are multiples commands and will handle
 * 		each commands separately in a fork. 
*/
int	pipex(t_list *list_commands, t_env *env)
{
	t_command	*command;
	int			pipes[2][2];

	command = list_commands->first;
	if (pipe(pipes[0]) == -1)
		return (print_perror());
	if (!first_cmd(list_commands, pipes, env))
		return (RETURN_FAILURE);
	command = command->next;
	while (command->next)
	{
		if (pipe(pipes[1]) == -1)
			return (print_perror());
		if (!middle_cmd(list_commands, command, pipes, env))
			return (RETURN_FAILURE);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		command = command->next;
	}
	if (!last_cmd(list_commands, command, pipes, env))
		return (RETURN_FAILURE);
	ft_waitpid(list_commands);
	return (RETURN_SUCCESS);
}
