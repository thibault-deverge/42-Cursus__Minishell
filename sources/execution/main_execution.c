#include "minishell.h"

t_list	*main_execution(t_list *lst, t_env *env)
{
	int	fdin;
	int	fdout;

	if (!lst || !lst->first)
		return (NULL);
	else if (!lst->first->next)
	{
		fdin = dup(0);
		fdout = dup(1);
		redi_manager(lst->first);
		if (!check_builtins(lst->first, env))
		{
			if (dup2(fdout, 1) < 0)
				return (NULL);
			printf("not builtin\n");
		}
		if (dup2(fdin, 0) < 0)
			return (NULL);
		close(fdin);
		if (dup2(fdout, 1) < 0)
			return (NULL);
		close(fdout);
		if (lst->first->fds[0] >= 0)
			close(lst->first->fds[0]);
		if (lst->first->fds[1] >= 0)
			close(lst->first->fds[1]);
	}
	else
	{
		printf("pipe.s\n");
		//pipex(lst->first);
	}
	return (0);
}
