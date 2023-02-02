#include "minishell.h"

/*
 * @summary:
 * 		- Initialize a structure of type 't_command', set all
 * 		its properties to NULL and return it.
*/
t_command	*initialize_command(void)
{
	t_command	*command;

	command = malloc(sizeof(t_command) * 1);
	if (!command)
		return (0);
	command->cmd = NULL;
	command->redi = NULL;
	command->next = NULL;
	return (command);
}

/*
 * @summary:
 * 		- Iterate through the linked list 'token' and assemble all the
 * 		consecutive commands in one string then return it.
 * 		- Use to check if multiple commands are consecutives and need to
 * 		be concatenated in one string.
*/
int	handle_command(t_command *command, t_token *token)
{
	t_token	*token_tmp;
	char	*command_tmp;
	char	*command_join;
	int		i;

	i = 1;
	token_tmp = token->next;
	if (token->rule == SPACEBAR)
		return (1);
	command_tmp = ft_strdup(token->arg);
	command_join = command_tmp;
	while (is_command(token_tmp))
	{
		if (!command_tmp || !command_join)
			return (print_perror());
		command_join = ft_strjoin(command_tmp, token_tmp->arg);
		free(command_tmp);
		command_tmp = command_join;
		token_tmp = token_tmp->next;
		i++;
	}
	command->cmd = insert_matrix(command->cmd, command_join);
	free(command_join);
	return (i);
}
