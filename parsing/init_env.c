#include "minishell.h"

static void	init_ascii_index(t_data *data)
{
	t_env	*tmp_sort;
	t_env	*tmp_index;
	int	i;

	tmp_index = data->envp;
	tmp_sort = data->envp->next;
	while (tmp_index)
	{
		while (tmp_sort)
		{
			i = 0;
			while (tmp_index->name[i] && tmp_sort->name[i] && tmp_index->name[i] == tmp_sort->name[i])
				i++;
			if (!tmp_index->name[i])
				tmp_sort = tmp_sort->next;
			else if ((!tmp_sort->name[i]) || (tmp_index->name[i] - 48) > (tmp_sort->name[i] - 48))
			{
				tmp_index->index += 1;
				tmp_sort = tmp_sort->next;
			}
			else if (tmp_index->name[i] < tmp_sort->name[i])
				tmp_sort = tmp_sort->next;
		}
		tmp_sort = data->envp;
		tmp_index = tmp_index->next;
	}
}

static t_env	*to_fill_env_data(t_env *envp, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	envp->name = malloc(sizeof(char) * (i + 1));
	if (!envp->name)
		return (NULL);
	envp->content = malloc(sizeof(char) * ((int)ft_strlen(str) - i + 1));
	if (!envp->content)
		return (NULL);
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
		i++;
	}
	init_ascii_index(data);
}
