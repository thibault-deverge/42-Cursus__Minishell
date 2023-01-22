#include "minishell.h"

void	print_envp(t_data *data)
{
	t_env	*tmp;

	tmp = data->envp;
	printf("env :\n");
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	print_export(t_data *data)
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
			if (tmp->content)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
			else
				printf("declare -x %s\n", tmp->name);
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
	export("toto", &data);
	export("titi=tutu", &data);
	export("riri=titi", &data);
	export(NULL, 0, &data);
	print_envp(&data);
	//print_export(&data);
}
