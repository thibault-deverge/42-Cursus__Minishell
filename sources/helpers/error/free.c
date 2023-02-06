#include "minishell.h"

/*
 * @summary:
 * 		- Free all linked lists by calling their respectives functions.
 * 		- Parameters needed are the head node of the list.
*/
void	free_all(t_variable *var, t_command *cmd, t_token *tok)
{
	free_env(var);
	free_commands(cmd);
	free_tokens(tok);
}

/*
 * @summary:
 * 		- Loop through the environment and free every variable with its content.
*/
void	free_env(t_variable *var)
{
	t_variable	*tmp;

	if (!var)
		return ;
	tmp = var;
	while (var)
	{
		var = var->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
		tmp = var;
	}
}

/*
 * @summary:
 * 		- Loop through t_list linked list and free every command's node and
 * 		its content.
*/
void	free_commands(t_command *command)
{
	t_command	*tmp;

	if (!command)
		return ;
	tmp = command;
	while (command)
	{
		command = command->next;
		free_matrix(tmp->cmd);
		free_matrix(tmp->redi);
		free(tmp);
		tmp = command;
	}
}

/*
 * @summary:
 * 		- Loop through parse linked list and free every tokens' node and
 * 		its content.
*/
void	free_tokens(t_token *token)
{
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (token)
	{
		token = token->next;
		free(tmp->arg);
		tmp = token;
	}
}

/*
 * @summary:
 * 		- Iterate throught the matrice and free every strings it contains.
 * 		- Free the matrice itself.
*/
void	free_matrix(char **matrice)
{
	int	i;

	i = 0;
	if (!matrice)
		return ;
	while (matrice[i])
	{
		free(matrice[i]);
		i++;
	}
	free(matrice);
}

/*
 * @summary:
 * 		- Call free_matrix() and free both matrices passed
 * 		as parameter.
*/
void	free_matrices(char **matrix1, char **matrix2)
{
	free_matrix(matrix1);
	free_matrix(matrix2);
}
