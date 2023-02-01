#include "minishell.h"

/*
 * @summary:
 * 		- Receive an int 'next_token' as parameter and traverse its value
 * 		throught the linked list to keep up with the parsing.
*/
static t_token	*traverse_next_token(t_token *token, int next_token)
{
	t_token	*tmp_token;
	int		i;

	i = 0;
	tmp_token = token;
	while (i < next_token)
	{
		tmp_token = tmp_token->next;
		i++;
	}
	return (tmp_token);
}

/*
 * @summary:
 * 		- Iterate throught the list_tokens and populate the list_commands
 * 		with the corrects values.
 * 		- Every command will have two matrices : one with the command and its
 * 		arguments and the other with the redirections and corresponding files.
 * 		- Return 'list_commands' updated or NULL if an error occured.
*/
t_list	*parse_commands(t_list *list_commands, t_parse *list_tokens)
{
	t_token		*token;
	t_command	*command;
	int			next_token;

	token = list_tokens->token;
	command = initialize_command();
	list_commands->first = command;
	while (token)
	{
		next_token = 1;
		if (is_pipe(token->arg) && token->rule == REDI)
		{
			command->next = initialize_command();
			command = command->next;
		}
		else if (is_redirection(token->arg) && token->rule == REDI)
			next_token = handle_redirection(command, token);
		else
			next_token = handle_command(command, token);
		if (!next_token)
			return (NULL);
		token = traverse_next_token(token, next_token);
	}
	return (list_commands);
}