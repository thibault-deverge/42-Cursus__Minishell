#include "minishell.h"

static int	get_nb_var(t_env *env)
{
	t_variable	*tmp;
	int			nb_var;

	nb_var = 0;
	tmp = env->var;
	while (tmp)
	{
		nb_var++;
		tmp = tmp->next;
	}
	return (nb_var);
}

char	**convert_env(t_env	*env)
{
	char		**envp;
	t_variable	*tmp;
	int			i;

	i = 0;
	envp = malloc(sizeof(char *) * (get_nb_var(env) + 1));
	if (!envp)
		return (NULL);
	tmp = env->var;
	while (tmp)
	{
		envp[i] = ft_sepjoin(tmp->name, tmp->content, '=');
		if (!envp[i])
		{
			free_matrix(envp);
			return (NULL);
		}
		tmp = tmp->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
