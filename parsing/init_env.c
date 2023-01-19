#include "minishell.h"

static t_env	*to_fill_env_data(t_env *envp, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	envp->name = malloc(sizeof(char) * (i + 1));
	envp->content = malloc(sizeof(char) * (strlen(str) - i + 1));
	i = 0;
	while (str[i] && str[i] != '=')
	{
		envp->name[i] = str[i];
		i++;
	}
	i++;
	while (str[i + j])
	{
		envp->content[j] = str[i + j];
		j++;
	}
	return (envp);
}

static t_data	*add_env(t_data *data, char *str)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new = to_fill_env_data(new, str);
	new->next = NULL;
	if (!data->envp)
		data->envp = new;
	else
	{
		tmp = data->envp;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (data);
}

void	get_envp(t_data *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		data = add_env(data, env[i]);
		i++;
	}
}
