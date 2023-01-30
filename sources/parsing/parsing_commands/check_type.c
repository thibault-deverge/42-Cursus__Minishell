#include "minishell.h"

/*
 * @summary:
 * 		- Check if the string passed as parameter is a pipe to
 * 		handle it as a delimiter of command.
*/
int	is_pipe(char *token)
{
	if (!ft_strcmp(token, "|"))
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Check is the string passed as parameter begin include
 * 		a redirection in its two first characters.
*/
int	is_redirection(char *token)
{
	if (!ft_strncmp(token, "<", 1) || !ft_strncmp(token, "<<", 2))
		return (1);
	else if (!ft_strncmp(token, ">", 1) || !ft_strncmp(token, ">>", 2))
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Check if char 'c' passed as a character is not a redirection
 * 		or a pipe.
 * 		- Use to check the third character of a redirection to check if 
 * 		this one is valid or not (because contains three '<' or '>').
*/
int	is_redirection_invalid(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Check the arg passed as parameter is in a command-form.
 * 		- Use to check if command are stick to another via multiple tokens
 * 		consecutively without space between. Allow to parse them in one string.
*/
int	is_command(t_token *token)
{
	if (!token || !token->arg)
		return (0);
	if (token->arg[0] == ' ' || token->rule != COMMAND)
		return (0);
	return (1);
}
