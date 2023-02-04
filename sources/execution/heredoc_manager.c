#include "minishell.h"

static int	store_str(t_command *command, char *str)
{
	if (command->fds[0] >= 0)
	{
		close(command->fds[0]);
		close(command->fds[1]);
	}
	if (!str)
		return (0);
	if (pipe(command->fds) < 0 || write(command->fds[1], str, ft_strlen(str) <= 0))
	{
		free(str);
		str = NULL;
		return (1);
	}
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
		command->fds[0] = -1;
		command->fds[1] = -1;
		while (command->redi && command->redi[i])
		{
			if (ft_strcmp(command->redi[i], "<<") == 0)
				if (set_heredoc(command, i) == 1)
					return (-1);
			i += 2;
		}
		command = command->next;
	}
	return (0);
}
