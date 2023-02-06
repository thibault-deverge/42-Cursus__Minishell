#include "minishell.h"

/*
 * @summary:
 * 		- Check if the command we are handling is the last one.
*/
int	is_last_command(t_command *command)
{
	if (!command->next)
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Print errno if parameter 'is_perror' is truthy.
 * 		- Free list of commands and envirornment then exit program.
*/
void	exit_child(t_list *list_cmd, t_env *env, int is_perror)
{
	if (is_perror)
		print_perror();
	free_env(env->var);
	free_commands(list_commands->first);
	exit(ERROR_BUILTIN);
}

/*
 * @summary:
 * 		- Dup2() the pipes to stdin and stdout depend which
 * 		command we are handling (first, middle or last).
*/
int	make_dup_cmd(int **pipes, int idx_cmd)
{
	if (idx_cmd == FIRST_CMD)
	{
		if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
			return (print_perror());
	}
	else
	{
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			return (print_perror());
		if (idx_cmd == MIDDLE_CMD)
		{
			if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
				return (print_perror());
		}
	}
}
