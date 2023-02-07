#include "minishell.h"

t_list	*main_parsing(t_list *lst, char *cmd, t_env *env)
{
	t_parse	parse;

	parse.token = NULL;
	if (!pre_parse(&parse, cmd, env))
	{
		free_tokens((&parse)->token);
		return (0);
	}
	if (!parse_commands(lst, &parse))
	{
		free_commands(lst->first);
		free_tokens((&parse)->token);
		return (0);
	}
	free_tokens((&parse)->token);
	return (lst);
}
