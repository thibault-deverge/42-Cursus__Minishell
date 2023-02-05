#include "minishell.h"

static void	update_dup(t_command *command, int fdin, int fdout)
{
	if (fdin >= 0)
	{
		if (command->fds[1] >= 0)
			close(command->fds[0]);
		command->fds[1] = fdin;
	}
	if (fdout >= 0)
	{
		if (command->fds[0] >= 0)
			close(fdout);
		else
			command->fds[0] = fdout;
	}
	if (command->fds[0] >= 0)
	{
		if (dup2(command->fds[0], 1) < 0)
			return ;
		close (command->fds[0]);
	}
	if (command->fds[1] >= 0)
	{
		if (dup2(command->fds[1], 0) < 0)
			return ;
		close (command->fds[1]);
	}
}

static int	open_file(char *file, int old_fd, int status)
{
	int	new_fd;

	new_fd = -1;
	if (old_fd >= 0)
		close(old_fd);
	if (status == 1)
		new_fd = open(file, O_RDONLY);
	else if (status == 2)
		new_fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (status == 3)
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

	fdin = -1;
	fdout = -1;
	i = 0;
	while (command->redi && command->redi[i])
	{
		if (ft_strcmp(command->redi[i], "<") == 0)
			fdin = open_file(command->redi[i + 1], fdin, 1);
		else if (ft_strcmp(command->redi[i], ">") == 0)
			fdout = open_file(command->redi[i + 1], fdout, 2);
		else if (ft_strcmp(command->redi[i], ">>") == 0)
			fdout = open_file(command->redi[i + 1], fdout, 3);
		i += 2;
	}
	update_dup(command, fdin, fdout);
}
