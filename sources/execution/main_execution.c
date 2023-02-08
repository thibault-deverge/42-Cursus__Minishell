#include "minishell.h"

static int	init_table_pid(t_list *lst)
{
	t_command	*tmp;

	tmp = lst->first;
	lst->nb_cmd = 0;
	while (tmp)
	{
		tmp->index = lst->nb_cmd;
		lst->nb_cmd++;
		tmp = tmp->next;
	}
	lst->pid = malloc(sizeof(int) * (lst->nb_cmd + 1));
	if (!lst->pid)
		return (print_perror());
	return (RETURN_SUCCESS);
}

int	main_execution(t_list *lst, t_env *env)
{
	int		fdin;
	int		fdout;

	if (!lst || !lst->first)
		return (RETURN_FAILURE);
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
	{
		env->envp = convert_env(env);
		if (!env->envp || !init_table_pid(lst))
			return (print_perror());
		pipex(lst, env);
		free(lst->pid);
	}
	return (RETURN_SUCCESS);
}
