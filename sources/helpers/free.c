#include "minishell.h"

void	free_env(t_variable *var)
{
	t_variable	*tmp;

	if (!env)
		return ;
	tmp = var;
	while (env)
	{
		var = var->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
}
