#include "minishell.h"

static int	store_str(t_command *command, char *str)
{
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (!str)
		return (0);
	if (!pipe(command->fds) && write(command->fds[1], str, ft_strlen(str)) <= 0)
	{
		free(str);
		str = NULL;
		return (1);
	}
	close (command->fds[1]);
	command->fds[1] = NO_FILE;
	free(str);
	str = NULL;
	return (0);
}

static int	set_heredoc(t_command *command, int index)
{
	char	*new_line;
	char	*content;

	content = NULL;
	new_line = readline("heredoc>");
	if (!new_line)
		return (1);
	while (ft_strcmp(new_line, command->redi[index + 1]) != 0)
	{
		content = ft_strjoin_safe(content, new_line);
		content = ft_strjoin_safe(content, "\n");
		if (!content)
			return (1);
		new_line = readline("heredoc>");
		if (!new_line)
		{
			free(content);
			content = NULL;
			return (1);
		}
	}
	if (store_str(command, content) == 1)
		return (1);
	return (0);
}

int	heredoc_manager(t_list *lst)
{
	t_command	*command;
	int		i;

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
				if (set_heredoc(command, i) == 1)
					return (-1);
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
	return (0);
}
