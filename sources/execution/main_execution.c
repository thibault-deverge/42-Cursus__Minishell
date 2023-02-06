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
			single_cmd(lst, lst->first, env);
		restore_fd(lst->first, fdin, fdout);
	}
	else
		pipex(lst, env);
	return (0);
}
