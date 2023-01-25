#include "minishell.h"

/*
 * @summary:
 * 		- Initialize a variable node and traverse to last element added.
 * 		- Compare last element added with every other element and update 
 * 		its index everytime the last element is bigger than another one
 * 		in ASCII.
*/
void	init_ascii_index(t_env *env)
{
	t_variable	*tmp_env;
	t_variable	*tmp_var;

	tmp_var = env->var;
	tmp_env = env->var;
	while (tmp_var->next)
		tmp_var = tmp_var->next;
	while (tmp_env != tmp_var)
	{
		if (strcmp(tmp_var->name, tmp_env->name) > 0)
			tmp_var->index++;
		else
			tmp_env->index++;
		tmp_env = tmp_env->next;
	}
}

/*
 * @summary:
 * 		- Loop through environment and add every variable to 
 * 		a linked list 'env' passed as parameter.
 * 		- Call a function to initialize its index based 
 * 		on ASCII order.
*/
void	get_env(t_env *env, char **envp)
{
	int	i;

	i = 0;
	env->var = NULL;
	while (envp[i])
	{
		env = insert_var_node(env, envp[i]);
		if (!env)
		{
			free_env(env->var);
			throw_perror(EXIT_ALLOC);
		}
		init_ascii_index(env);
		i++;
	}
}
