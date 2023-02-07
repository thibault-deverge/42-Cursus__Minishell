#include "minishell.h"

t_variable	*get_last_var(t_env *env)
{
	t_variable	*tmp;

	if (!env->var)
		return (NULL);
	tmp = env->var;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_variable	*add_new_variable(char *var, int len, t_env *env)
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
	if (!new->name)
		return (NULL);
	new->content = NULL;
	init_ascii_index(env);
	return (new);
}

int	manage_variable(char *new_var, t_env *env)
{
	int			key_len;
	t_variable	*var_env;

	key_len = get_key_len(new_var);
	if (!key_len)
	{
		if (!manage_key(new_var, ft_strlen(new_var), env))
			return (RETURN_FAILURE);
	}
	else if (new_var[key_len - 1] == '+')
	{
		var_env = manage_key(new_var, key_len - 1, env);
		if (var_env && !add_new_content(var_env, &new_var[key_len + 1]))
			return (RETURN_FAILURE);
	}
	else
	{
		var_env = manage_key(new_var, key_len, env);
		if (var_env && !set_new_content(var_env, &new_var[key_len + 1]))
			return (print_perror());
	}
	return (RETURN_SUCCESS);
}

