#include "minishell.h"

static void	update_ascii_index(int index, t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->index > index)
			tmp->index--;
		tmp = tmp->next;
	}
}

static void	delete_var(int index, t_env *env)
{
	t_variable	*tmp;
	t_variable	*tmp_del;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->next->index == index)
		{
			tmp_del = tmp->next;
			tmp->next = tmp->next->next;
			free(tmp_del->name);
			free(tmp_del->content);
			free(tmp_del);
			tmp_del = NULL;
			return ;
		}
		tmp = tmp->next;
	}
}

int	unset(t_command *command, t_env *env)
{
	int		i;
	int		len_cmd;
	int		index;
	t_variable	*var;

	i = 1;
	while (command->cmd[i])
	{
		len_cmd = ft_strlen(command->cmd[i]);
		if (!check_key_name(command->cmd[i], len_cmd, "unset"))
			return (1);
		var = get_variable(env, command->cmd[i], len_cmd);
		if (var)
		{
			index = var->index;
			delete_var(index, env);
			update_ascii_index(index, env);
		}
		i++;
	}
	return (0);
}
