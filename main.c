#include "minishell.h"

static void	print_envp(t_data *data)
{
	t_env	*tmp;

	tmp = data->envp;
	printf("env :\n");
	while (tmp)
	{
		printf("%s = %s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

static void	print_export(t_data *data)
{
	int	index;
	t_env	*tmp;

	index = 0;
	tmp = data->envp;
	printf("\nexport :\n");
	while (tmp)
	{
		if (index == tmp->index)
		{
			printf("declare -x %s = %s\n", tmp->name, tmp->content);
			tmp = data->envp;
			index++;
		}
		else
			tmp = tmp->next;
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
	print_export(&data);
}
