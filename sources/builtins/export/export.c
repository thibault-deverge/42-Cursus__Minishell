#include "minishell.h"

/*
 * @summary:
 * 		- Print complete error in the form :
 * 		"<err_src>: '<err_sub>': <err_msg>"
*/
int	export_error(char *src, char *sub, int len, char *err_msg)
{
	int	i;

	i = 0;
	ft_putstr_fd(src, 2);
	ft_putstr_fd(": \'", 2);
	while (i < len)
	{
		ft_putchar_fd(sub[i], 2);
		i++;
	}
	ft_putstr_fd("\': ", 2);
	ft_putstr_fd(err_msg, 2);
	return (RETURN_FAILURE);
}

/*
 * @summary:
 * 		- Loop through the environment linked list and print all variable
 * 		as the command 'export' would do using ASCII order.
*/
static void	print_export(t_env *env)
{
	int			index;
	t_variable	*tmp;

	index = 0;
	tmp = env->var;
	while (tmp)
	{
		if (index == tmp->index)
		{
			if (tmp->content && ft_strcmp(tmp->name, "_") != 0)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
			else if (!tmp->content && ft_strcmp(tmp->name, " ") != 0)
				printf("declare -x %s\n", tmp->name);
			tmp = env->var;
			index++;
		}
		else
			tmp = tmp->next;
	}
}

/*
 * @summary:
 * 		- Print environment by ASCII order if no arguments are passed.
 * 		- Export variable passed as parameters if arguments are passed
 * 		to the built-in.
*/
int	exec_export(t_command *command, t_env *env)
{
	int	i;

	i = 1;
	if (!command->cmd[i])
	{
		print_export(env);
		return (RETURN_SUCCESS);
	}
	while (command->cmd[i])
	{
		if (!manage_variable(command->cmd[i], env))
			return (RETURN_FAILURE);
		i++;
	}
	return (RETURN_SUCCESS);
}
