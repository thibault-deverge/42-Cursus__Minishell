#include "minishell.h"

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
