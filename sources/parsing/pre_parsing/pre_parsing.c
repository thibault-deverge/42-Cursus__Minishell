#include "minishell.h"

static void	print_arg(t_parse *parse)
{
	t_token	*tmp;

	tmp = parse->token;
	//printf("\nARG LIST : \n");
	while (tmp)
	{
		//printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}


/*
 * @summary:
 * 		- Iterate throught the string of commands, character by character, as long as it doesn't matches to a useful argument in split of parsing.
 *		- Return the new linked list with only valid arguments for 2nd part of parsing.
*/

t_parse	*pre_parse(t_parse *parse, char *cmd, t_env *env)
{
	int		len;
	int		start;

	start = 0;
	len = 0;
	while (cmd[len])
	{
		if (check_arg(cmd[len]) != 0)
		{
			len = manage_arg(&cmd[start], parse, len - start, env);
			if (!len)
				return (NULL);
			len += start;
			start = len;
		}
		else
			len++;
	}
	add_new_token(cmd, start, len, parse);
	print_arg(parse);
	return (parse);
}
