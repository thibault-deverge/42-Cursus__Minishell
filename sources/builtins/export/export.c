#include "minishell.h"

/*static void	check_variable(t_env *envp)
{
	t_variable	*tmp_command;
	t_variable	*tmp_env;

	tmp_command = envp->variable;
	tmp_env = envp->variable;
	while (tmp_command->next)
		tmp_command = tmp_command->next;
	while (tmp_command->content && tmp_env->next)
	{
		if (tmp_env->content && ft_strncmp(tmp_command->content, tmp_env->name,
				ft_strlen(tmp_command->content) + 1) == 0)
		{
			free(tmp_command->content);
			tmp_command->content = ft_substr(tmp_env->content, 0, ft_strlen(tmp_env->content));
		}
		tmp_env = tmp_env->next;
	}
}*/



void	export(t_command *command, t_env *env)
{
	int	i;

	i = 1;
	if (!command[i])
	{
		print_export(env);
		return ;
	}
	while (command[i])
	{
		manage_variable(command[i], env);
		i++;
	}
}
