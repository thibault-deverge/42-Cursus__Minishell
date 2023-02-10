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

static int	restore_fd(t_command *command, int fdout, int fdin)
{
	if (fdout > 0)
	{
		if (!dup2(fdout, 1))
			return (1);
		close(fdout);
	}
	if (fdin > 0)
	{
		if (!dup2(fdin, 0))
			return (1);
		close(fdin);
	}
	if (command->fds[0] != NO_FILE)
		close(command->fds[0]);
	if (command->fds[1] != NO_FILE)
		close(command->fds[1]);
	return (0);
}

int	main_execution(t_list *lst, t_env *env)
{
	int	fdout;
	int	fdin;

	modify_signals(CMD_SIGNAL);
	if (!lst || !lst->first)
		return (RETURN_FAILURE);
	else if (!lst->first->next)
	{
		fdout = -1;
		fdin = -1;
		if (is_builtin(lst->first) && lst->first->redi)
		{
			fdout = dup(1);
			fdin = dup(0);
			if (!redi_manager(lst->first))
				return (RETURN_FAILURE);
		}
		if (!check_builtins(lst->first, env))
			single_cmd(lst, lst->first, env);
		restore_fd(lst->first, fdout, fdin);
	}
	else
	{
		env->envp = convert_env(env);
		if (!env->envp || !init_table_pid(lst))
			return (print_perror());
		pipex(lst, env);
		free(lst->pid);
		free_matrix(env->envp);
	}
	return (RETURN_SUCCESS);
}
