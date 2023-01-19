#include "minishell.h"

static void	print_envp(t_data *data)
{
	while (data->envp)
	{
		printf("%s = %s\n", data->envp->name, data->envp->content);
		data->envp = data->envp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	(void)argc;
	(void)argv;
	data.envp = NULL;
	get_envp(&data, env);
	print_envp(&data);
}
