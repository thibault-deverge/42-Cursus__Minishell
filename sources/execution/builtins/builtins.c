#include "minishell.h"

static const t_builtins	*get_builtins(void)
{
	static const t_builtins	builtins[7] = {{"export", exec_export}, \
										{"env", exec_env}, \
										{"echo", exec_echo}, \
										{"unset", exec_unset}, \
										{"pwd", exec_pwd}, \
										{"cd", exec_cd}, \
										{"exit", exec_exit}};

	return (builtins);
}

int	check_builtins(t_command *command, t_env *env)
{
	const t_builtins	*builtins;
	int					i;

	builtins = get_builtins();
	i = 0;
	while (i < 7)
	{
		if (command->cmd && ft_strcmp(command->cmd[0], builtins[i].name) == 0)
		{
			if (!builtins[i].f(command, env))
				return (-1);
			g_value = 0;
			return (1);
		}
		i++;
	}
	return (0);
}
