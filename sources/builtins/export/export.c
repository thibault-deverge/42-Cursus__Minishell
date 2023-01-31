#include "minishell.h"

static int	get_key_len(char *var)
{
	int	i;

	i = 0;
	while(var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (0);
	return (i);
}

static int	check_key_name(char *key, int len)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]))
		return (0);
	while (i < len)
	{
		i++;
	}
	return (1);
}

static void	set_new_content(t_variable *var, char *value)
{
	var->content = ft_strdup(value);
}

static void	add_new_content(t_variable *var, char *value)
{
	if (!var->content)
		set_new_content(var, value);
	else
		var->content = ft_strjoin(var->content, value);
}

static t_variable	*get_last_var(t_env *env)
{
	t_variable	*tmp;

	if (!env->var)
		return (NULL);
	tmp = env->var;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

static t_variable	*add_new_variable(char *var, int len, t_env *env)
{
	t_variable	*new;
	t_variable	*tmp;

	new = malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->index = 0;
	if (!env->var)
		env->var = new;
	else
	{
		tmp = get_last_var(env);
		tmp->next = new;
	}
	new->name = ft_substr(var, 0, len);
	new->content = NULL;
	init_ascii_index(env);
	return (new);
}

static t_variable	*manage_key(char *new_var, int key_len, t_env *env)
{
	t_variable	*var_env;

	var_env = get_variable(env, new_var, key_len - 1);
	if (var_env)
		return (var_env);
	else if (check_key_name(new_var, key_len))
	{
		add_new_variable(new_var, key_len, env);
		return (get_last_var(env));
	}
	else
		return (NULL);
}

static void	manage_variable(char *new_var, t_env *env)
{
	int			key_len;
	t_variable	*var_env;

	key_len = get_key_len(new_var);
	if (!key_len)
		manage_key(new_var, ft_strlen(new_var), env);
	else if (new_var[key_len - 1] == '+')
	{
		var_env = manage_key(new_var, key_len - 1, env);
		if (var_env)
			add_new_content(var_env, &new_var[key_len + 1]);
	}
	else
	{
		var_env = manage_key(new_var, key_len, env);
		if (var_env)
			set_new_content(var_env, &new_var[key_len + 1]);
	}
}

void	export(char **command, t_env *env)
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
