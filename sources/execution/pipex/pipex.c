#include "minishell.h"

static void	ft_waitpid(t_list *list_commands)
{
	int	i;

	i = 0;
	while (list_commands->pid[i])
	{
		waitpid(list_commands->pid[i], NULL, 0);
		i++;
	}
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
		return (0);
	command = command->next;
	while (command->next)
	{
		if (pipe(pipes[1]) == -1)
			return (print_perror());
		if (!middle_cmd(list_commands, command, pipes, env))
			return (0);
		pipes[0][0] = pipes[1][0];
		pipes[0][1] = pipes[1][1];
		command = command->next;
	}
	if (!last_cmd(list_commands, command, pipes, env))
		return (0);
	ft_waitpid(list_commands);
	return (1);
}
