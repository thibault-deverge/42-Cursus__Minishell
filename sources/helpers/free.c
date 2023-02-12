#include "minishell.h"

/*
 * @summary:
 * 		- Free linked list which contains environment and linked list
 * 		which contains commands and redirections.
*/
void	free_main_lists(t_command *command, t_env *env)
{	
	free_env(env->var);
	free_commands(command);
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
		free(tmp);
		tmp = NULL;
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
