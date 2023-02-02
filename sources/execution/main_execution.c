#include "minishell.h"

t_list	*main_execution(t_list *lst, t_env *env)
{
	t_command		*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if (!check_builtins(tmp, env))
			printf("not builtin\n");
		tmp = tmp->next;
	}
	return (0);
}
