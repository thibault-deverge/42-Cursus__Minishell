#include "minishell.h"

t_list	*main_execution(t_list *lst, t_env *env)
{
//	int	fd;

	if (!lst || !lst->first)
		return (NULL);
	else if (!lst->first->next)
	{
		//manage_redi(lst->first->redi);
		if (!check_builtins(lst->first, env))
			printf("not builtin\n");
	//	if (fd <= 0)
	}
	else
	{
		printf("pipe.s\n");
		//pipex(lst->first);
	}
	return (0);
}
