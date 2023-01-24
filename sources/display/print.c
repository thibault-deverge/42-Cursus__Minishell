#include "minishell.h"

void	print_env(t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	printf("env :\n");
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	print_export(t_env *env)
{
	int			index;
	t_variable	*tmp;

	index = 0;
	tmp = env->var;
	printf("\nexport :\n");
	while (tmp)
	{
		if (index == tmp->index)
		{
			if (tmp->content)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
			else
				printf("declare -x %s\n", tmp->name);
			tmp = env->var;
			index++;
		}
		else
			tmp = tmp->next;
	}
}
