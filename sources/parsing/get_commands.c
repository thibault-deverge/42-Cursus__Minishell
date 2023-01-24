#include "minishell.h"

t_list	*get_commands(t_parse *parse)
{
	t_token	*tmp;
	char	*commands;

	if (!parse->token)
		return (NULL);
	commands = ft_strdup(parse->token->arg);
	if (!commands)
		return (NULL);
	tmp = parse->token->next;
	while (tmp)
	{
		commands = ft_strjoin(commands, tmp->arg);
		tmp = tmp->next;
	}
	printf("Commands : %s\n", commands);
	return (NULL);
}
