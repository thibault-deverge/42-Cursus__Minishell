#include "minishell.h"

/*
 * @summary:
 * 		- Loop through the 'env' linked list and print every variables.
*/
void	print_env(t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

/*
 * @summary:
 * 		- Loop through the environment linked list and print all variable
 * 		as the built-in 'export' would do using ASCII order.
*/
void	print_export(t_env *env)
{
	int			index;
	t_variable	*tmp;

	index = 0;
	tmp = env->var;
	while (tmp)
	{
		if (index == tmp->index)
		{
			if (tmp->content && ft_strcmp(tmp->name, "_") != 0)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
			else if (!tmp->content && ft_strcmp(tmp->name, " ") != 0)
				printf("declare -x %s\n", tmp->name);
			tmp = env->var;
			index++;
		}
		else
			tmp = tmp->next;
	}
}
