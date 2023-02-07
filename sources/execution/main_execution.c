#include "minishell.h"

static int	init_table_pid(t_list *lst)
{
	t_command	*tmp;
	int			nb_cmd;

	tmp = lst->first;
	nb_cmd = 0;
	while (tmp)
	{
		tmp->index = nb_cmd;
		nb_cmd++;
		tmp = tmp->next;
	}
	lst->pid = malloc(sizeof(int) * nb_cmd);
	if (!lst->pid)
		return (print_perror());
	return (0);
}

t_list	*main_execution(t_list *lst, t_env *env)
{
	int		fdin;
	int		fdout;

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
	{
		init_table_pid(lst);
		pipex(lst, env);
		free(lst->pid);
	}
	return (0);
}
