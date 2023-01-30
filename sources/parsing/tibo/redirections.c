#include "minishell.h"

/*
 * @summary:
 * 		- Search the next file which follow the redirection found earlier
 * 		to add it to matrice 'redi' in the 't_command' structure.
 * 		- Print an error if a redirection follow another one and return (NULL)
 * 		- If valid file found, insert it to matrice and return number of token
 * 		need to be passed to continue parsing.
*/
static int	insert_file_to_redi(t_command *command, t_token *token)
{
	int	next_token;

	next_token = 1;
	while (token)
	{
		if (is_redirection(token->arg))
			return (print_error(ERROR_SYNTAX));
		if (!ft_strcmp(token->arg, " "))
			next_token++;
		else
		{
			next_token++;
			command->redi = insert_matrice(command->redi, token->arg);
			return (next_token);
		}
		token = token->next;
	}
	return (0);
}

/*
 * @summary:
 * 		- Insert redirection into matrice 'redi' in the command structure
 * 		- Check if the file associated to the redi is stick in the same token
 * 		to the redi and insert it to the matrice if it's the case.
 * 		- Return 1 if only redirection was inserted or 2 if file was stick to
 * 		redirection and de facto also inserted into the matrice.
*/
static int	insert_redirection(t_command *command, t_token *token, int redi_idx)
{
	char	*redi;

	redi = ft_substr(token->arg, 0, redi_idx);
	if (!redi)
		return (print_perror());
	command->redi = insert_matrice(command->redi, redi);
	free(redi);
	redi = NULL;
	if (token->arg[redi_idx])
	{
		redi = ft_substr(token->arg, redi_idx, ft_strlen(token->arg));
		if (!redi)
			return (0);
		command->redi = insert_matrice(command->redi, redi);
		free(redi);
		redi = NULL;
	}
	else
		return (1);
	return (2);
}

/*
 * @summary:
 * 		- Check if redirection is 1 or 2 character and if valid.
 * 		- Check and add word to matrice if the file follow the redirection
 * 		in the same node.
 * 		- If file targeted is not in same node, search next nodes to find it
 * 		and add it to the matrice.
 * 		- Return number of node we need to jump to continue parsing correctly.
*/
int	handle_redirection(t_command *command, t_token *token)
{
	int		nb_redi_inserted;
	int		nb_next_token;
	int		i;

	i = 1;
	if (token->arg[i] == '<' || token->arg[i] == '>')
		i++;
	if (is_redirection_invalid(token->arg[i]))
		return (print_error(ERROR_SYNTAX));
	nb_redi_inserted = insert_redirection(command, token, i);
	if (!nb_redi_inserted)
		return (0);
	if (nb_redi_inserted == 2)
		return (1);
	nb_next_token = insert_file_to_redi(command, token->next);
	if (!nb_next_token)
		return (print_error(ERROR_SYNTAX));
	return (nb_next_token);
}
