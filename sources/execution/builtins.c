#include "minishell.h"

static const t_builtins	*get_builtins(void)
{
	static const t_builtins	builtins[5] = {{"export", export}, \
										{"env", env}, \
										{"echo", exec_echo}, \
										{"unset", unset}, \
										{"pwd", exec_pwd}};
	return (builtins);
}

int	check_builtins(t_command *command, t_env *env)
{
	const t_builtins	*builtins;
	int			i;

	builtins = get_builtins();
	i = 0;
	while (i < 5)
	{
		if (command->cmd && ft_strcmp(command->cmd[0], builtins[i].name) == 0)
		{
			builtins[i].f(command, env);
			return (1);
		}
		i++;
	}
	return (0);
}

