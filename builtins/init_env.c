#include "minishell.h"

void	init_ascii_index(t_data *data)
{
	t_env	*tmp_env;
	t_env	*tmp_index;
	int	i;

	tmp_index = data->envp;
	tmp_env = data->envp;
	while (tmp_index->next)
		tmp_index = tmp_index->next;
	while (tmp_env != tmp_index)
	{
		i = 0;
		while (tmp_index->name[i] && tmp_env->name[i]
				&& tmp_index->name[i] == tmp_env->name[i])
			i++;
		if (!tmp_env->name[i] || (tmp_env->name[i] 
				&& tmp_index->name[i] - 48 > tmp_env->name[i] - 48))
			tmp_index->index += 1;
		else
			tmp_env->index += 1;
		tmp_env = tmp_env->next;
	}
}

static t_env	*to_fill_env_data(t_env *envp, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	envp->name = ft_substr(str, 0, i);
	if (!envp->name)
		return (NULL);
	if (i == ft_strlen(str))
		envp->content = NULL;
	else
	{
		envp->content = ft_substr(str, i + 1, ft_strlen(str));
		if (!envp->content)
			return (NULL);
	}
	return (envp);
}

t_data	*add_env(t_data *data, char *str)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new = to_fill_env_data(new, str);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->index = 0;
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
		if (!data)
		{
			//free all
			return ;
		}
		init_ascii_index(data);
		i++;
	}
}
