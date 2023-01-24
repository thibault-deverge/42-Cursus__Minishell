#include "minishell.h"

/*
 * @summary:
 * 		- A RAJOUTER
*/
void	init_ascii_index(t_env *env)
{
	t_variable	*tmp_env;
	t_variable	*tmp_var;
	int			i;

	tmp_var = env->var;
	tmp_env = env->var;
	while (tmp_var->next)
		tmp_var = tmp_var->next;
	while (tmp_env != tmp_var)
	{
		i = 0;
		while (tmp_var->name[i] && tmp_env->name[i]
			&& tmp_var->name[i] == tmp_env->name[i])
			i++;
		if (!tmp_env->name[i] || tmp_var->name[i] - 48 > tmp_env->name[i] - 48)
			tmp_var->index += 1;
		else
			tmp_env->index += 1;
		tmp_env = tmp_env->next;
	}
}

/*
 * @summary:
 * 		- Fill the information about environment variable passed as parameter
 * 		('str') to a node variable and return the node.
 * 		- Store first its name then its content in two distinct function.
*/
static t_variable	*to_fill_env_variable(t_variable *var, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->name = ft_substr(str, 0, i);
	if (!var->name)
		return (NULL);
	if (i == ft_strlen(str))
		var->content = NULL;
	else
	{
		var->content = ft_substr(str, i + 1, ft_strlen(str));
		if (!var->content)
			return (NULL);
	}
	return (var);
}

/*
 * @summary:
 * 		- Initialize a new variable in the heap and fill it
 * 		with information passed with the env variable 'str'.
 * 		- Add node variable at the end of linked list passed
 * 		as parameter ('end').
 * 		- return the linked list
*/
t_env	*add_variable(t_env *env, char *str)
{
	t_variable	*new;
	t_variable	*tmp;

	new = malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new = to_fill_env_variable(new, str);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->index = 0;
	if (!env->var)
		env->var = new;
	else
	{
		tmp = env->var;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (env);
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
		env = add_variable(env, envp[i]);
		if (!env)
		{
			//free all
			return ;
		}
		init_ascii_index(env);
		i++;
	}
}
