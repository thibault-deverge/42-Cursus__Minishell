#include "minishell.h"

t_list	*main_execution(t_list *lst, t_env *env)
{
	if (!lst->first)
		return (NULL);
	else if (!lst->first->next)
	{
		if (!check_builtins(lst->first, env))
			printf("not builtin\n");
	}
	else
	{
		printf("pipe.s\n");
		//pipex(lst->first);
	}
	return (0);
}
