#include "minishell.h"

char	*set_new_content(t_variable *var, char *value)
{
	var->content = ft_strdup(value);
	if (!var->content)
		return (NULL);
	return (var->content);
}

int	add_new_content(t_variable *var, char *value)
{
	if (!var->content)
	{
		if (!set_new_content(var, value))
			return (print_perror());
	}
	else
	{
		var->content = ft_strjoin(var->content, value);
		if (!var->content)
			return (print_perror());
	}
	return (RETURN_SUCCESS);
}
