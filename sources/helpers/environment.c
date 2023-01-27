#include "minishell.h"

/*
 * @summary:
 * 		- Initialize a new variable node and fill it with
 * 		information passed as parameter 'str'.
 * 		- Add node variable at the end of environment list.
 * 		- return the linked list
*/
t_env	*insert_var_node(t_env *env, char *str)
{
	t_variable	*new;
	t_variable	*tmp;

	new = malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new = set_var_content(new, str);
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
 * 		- Fill the information about environment variable passed as parameter
 * 		('str') to a node variable and return the node.
 * 		- Store first its name then its content in two distinct function.
*/
t_variable	*set_var_content(t_variable *var, char *str)
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
 * 		- Search in environment via name of the variable passed as parameter
 * 		and return its content.
*/
char	*get_var_content(t_env *env, char *var_name)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, var_name))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

/*
 * @summary:
 * 		- Search in environment via name of the variable passed as parameter
 * 		and return its pointer.
*/
t_variable	*get_variable(t_env *env, char *var_name)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, var_name))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
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
