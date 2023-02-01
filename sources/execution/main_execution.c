#include "minishell.h"

t_list	*main_execution(t_list *lst, t_env *env)
{
	t_command	*tmp;

	tmp = lst->first;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd[0], "export") == 0)
			export(tmp->cmd, env);
		tmp = tmp->next;
	}
	return (0);
}
