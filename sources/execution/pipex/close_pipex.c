#include "minishell.h"

/*
 * @summary:
 * 		- Check if files are open and close them if they are.
*/
void	close_files(t_command *command)
{
	if (command->fds[0] != -1)
		close(fds[0]);
	if (command->fds[1] != -1)
		close(fds[1]);
}

/*
 * @summary:
 * 		- Close both pipes at read and write exit.
*/
void	close_pipes(int **pipes)
{
	close_pipe(pipes[0]);
	close_pipe(pipes[1]);
}

/*
 * @summary:
 * 		- Close pipe passed as parameter.
*/
void	close_pipe(int *pipe)
{
	close(fd[0]);
	close(fd[1]);
}
