#include "minishell.h"

static int	print_heredoc_error(char *error)
{
	ft_putstr_fd(ERROR_HEREDOC, 2);
	ft_putstr_fd(" (wanted \'", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\')\n", 2);
	return (RETURN_FAILURE);
}

static int	store_str(t_command *command, char *str)
{
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (!str)
		return (1);
	if (!pipe(command->fds) && write(command->fds[1], str, ft_strlen(str)) <= 0)
	{
		free(str);
		str = NULL;
		return (RETURN_FAILURE);
	}
	close (command->fds[1]);
	command->fds[1] = NO_FILE;
	free(str);
	str = NULL;
	return (RETURN_SUCCESS);
}

static int	set_heredoc(t_command *command, int index)
{
	char	*new_line;
	char	*content;

	content = NULL;
	new_line = readline("heredoc>");
	if (!new_line)
		return (print_heredoc_error(command->redi[index + 1]));
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
			return (print_heredoc_error(command->redi[index + 1]));
		}
	}
	if (!store_str(command, content))
		return (print_perror());
	return (RETURN_SUCCESS);
}

int	heredoc_manager(t_list *lst)
{
	t_command	*command;
	int			i;

	command = lst->first;
	while (command)
	{
		i = 0;
		command->fds[0] = NO_FILE;
		command->fds[1] = NO_FILE;
		while (command->redi && command->redi[i])
		{
			if (ft_strcmp(command->redi[i], "<<") == 0 && !set_heredoc(command, i))
				return (RETURN_FAILURE);
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
