#include "minishell.h"

int	get_key_len(char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (!var[i])
		return (0);
	return (i);
}

int	check_key_name(char *key, int len, char *built)
{
	int	i;

	i = 0;
	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		export_error(built, key, len, INVALID_KEY);
		return (0);
	}
	while (i < len)
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			export_error(built, key, len, INVALID_KEY);
			return (0);
		}
		i++;
	}
	return (1);
}

t_variable	*manage_key(char *new_var, int key_len, t_env *env)
{
	t_variable	*var_env;

	var_env = get_variable(env, new_var, key_len - 1);
	if (var_env && ft_strcmp(var_env->name, "_") == 0)
		return (NULL);
	if (var_env)
		return (var_env);
	else if (check_key_name(new_var, key_len, "export"))
	{
		add_new_variable(new_var, key_len, env);
		return (get_last_var(env));
	}
	else
		return (NULL);
}
