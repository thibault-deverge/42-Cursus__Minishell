#include "minishell.h"

static void	update_dup(t_command *command, int fdin, int fdout)
{
	if (fdout != NO_FILE)
		command->fds[1] = fdout;
	if (fdin >= 0)
	{
		if (command->fds[0] != NO_FILE)
			close(command->fds[0]);
		command->fds[0] = fdin;
	}
	if (command->fds[1] != NO_FILE)
	{
		if (dup2(command->fds[1], 1) < 0)
			return ;
		close (command->fds[1]);
	}
	if (command->fds[0] != NO_FILE)
	{
		if (dup2(command->fds[0], 0) < 0)
			return ;
		close (command->fds[0]);
	}
}

static int	open_file(char *file, int old_fd, int status)
{
	int	new_fd;

	new_fd = -1;
	if (old_fd >= 0)
		close(old_fd);
	if (status == IN)
		new_fd = open(file, O_RDONLY);
	else if (status == OUT)
		new_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (status == ADD_OUT)
		new_fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (new_fd < 0)
		print_error(ERROR_OPEN_FD);
	return (new_fd);
}

void	redi_manager(t_command *command)
{
	int	i;
	int	fdin;
	int	fdout;

	fdin = NO_FILE;
	fdout = NO_FILE;
	i = 0;
	while (command->redi && command->redi[i])
	{
		if (ft_strcmp(command->redi[i], "<") == 0)
			fdin = open_file(command->redi[i + 1], fdin, IN);
		else if (ft_strcmp(command->redi[i], ">") == 0)
			fdout = open_file(command->redi[i + 1], fdout, OUT);
		else if (ft_strcmp(command->redi[i], ">>") == 0)
			fdout = open_file(command->redi[i + 1], fdout, ADD_OUT);
		i += 2;
	}
	update_dup(command, fdin, fdout);
}
