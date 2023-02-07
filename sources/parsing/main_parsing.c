#include "minishell.h"

t_list	*main_parsing(t_list *lst, char *cmd, t_env *env)
{
	t_parse	parse;

	parse.token = NULL;
	if (!pre_parse(&parse, cmd, env))
	{
		free(cmd);
		free_tokens((&parse)->token);
		return (RETURN_FAILURE);
	}
	if (!parse_commands(lst, &parse))
	{
		free(cmd);
		free_all(NULL, lst->first, (&parse)->token);
		return (RETURN_FAILURE);
	}
	free_tokens((&parse)->token);
	return (lst);
}
