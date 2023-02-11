#include "minishell.h"

static int	print_heredoc_error(char *error, int stdin_dup)
{
	int	check_stdin;

	check_stdin = dup(0);
	if (check_stdin == -1)
	{
		dup2(stdin_dup, 0);
		close(stdin_dup);
	}
	else
	{
		close(check_stdin);
		ft_putstr_fd(ERROR_HEREDOC, 2);
		ft_putstr_fd(" (wanted \'", 2);
		ft_putstr_fd(error, 2);
		ft_putstr_fd("\')\n", 2);
	}
	return (RETURN_FAILURE);
}

static int	store_str(t_command *command, char *str)
{
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (pipe(command->fds))
	{
		if (str)
			free(str);
		return (RETURN_FAILURE);
	}
	if (str && write(command->fds[1], str, ft_strlen(str)) <= 0)
	{
		free(str);
		return (RETURN_FAILURE);
	}
	close (command->fds[1]);
	command->fds[1] = NO_FILE;
	free(str);
	return (RETURN_SUCCESS);
}

static int	set_heredoc(t_command *command, int index, int stdin_dup)
{
	char	*new_line;
	char	*content;

	content = NULL;
	new_line = readline("heredoc>");
	if (!new_line)
		return (print_heredoc_error(command->redi[index + 1], stdin_dup));
	while (ft_strcmp(new_line, command->redi[index + 1]) != 0)
	{
		content = ft_strjoin_safe(content, new_line);
		content = ft_strjoin_safe(content, "\n");
		if (!content)
			return (print_perror());
		new_line = readline("heredoc>");
		if (!new_line)
		{
			free(content);
			content = NULL;
			return (print_heredoc_error(command->redi[index + 1], stdin_dup));
		}
	}
	if (!store_str(command, content))
		return (print_perror());
	return (RETURN_SUCCESS);
}

int	heredoc_manager(t_list *lst)
{
	t_command	*command;
	int			stdin_dup;
	int			i;

	command = lst->first;
	while (command)
	{
		i = 0;
		command->fds[0] = NO_FILE;
		command->fds[1] = NO_FILE;
		while (command->redi && command->redi[i])
		{
			if (ft_strcmp(command->redi[i], "<<") == 0)
			{
				stdin_dup = set_signal_heredoc();
				if (!set_heredoc(command, i, stdin_dup))
					return (RETURN_FAILURE);
			}
			else if (ft_strcmp(command->redi[i], "<") == 0 && command->fds[0] != NO_FILE)
			{
				close(command->fds[0]);
				command->fds[0] = NO_FILE;
			}
			i += 2;
		}
		command = command->next;
	}
	return (RETURN_SUCCESS);
}
