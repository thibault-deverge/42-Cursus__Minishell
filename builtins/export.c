#include "minishell.h"

static void	check_variable(t_data *data)
{
	t_env	*tmp_command;
	t_env	*tmp_env;

	tmp_command = data->envp;
	tmp_env = data->envp;
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
}

void	export(char *cmd, bool pipe, t_data *data)
{
	if (!cmd && !pipe)
		print_export(data);
	else if (!cmd && pipe)
		return ;
	else
	{
		add_env(data, cmd);
		init_ascii_index(data);
		check_variable(data);
	}
}
