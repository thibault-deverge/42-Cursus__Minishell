#include "minishell.h"

static int	manage_key_value(char *arg, t_parse *parse, t_env *env)
{
	int		i;
	char	*add_content;

	i = 1;
	add_content = NULL;
	while (arg[i] && arg[i] != ' ' && arg[i] != '"' && arg[i] != '\'')
		i++;
	if (i > 1)
		add_content = get_value_of_key(&arg[1], i - 1, env);
	if (add_content)
		add_new_token(add_content, 0, ft_strlen(add_content), parse);
	else if (i == 1)
		add_new_token(arg, 0, 1, parse);
	else if (!ft_isalpha(arg[1]))
		add_new_token(arg, 2, i, parse);
	return (i);
}

/*
 * @summary:
 *		- 
*/
static int	manage_double_quotes(char *arg, t_parse *parse, t_env *env)
{
	int	i;
	int	start;

	i = 1;
	start = 1;
	while (arg[i] != '"')
	{
		if (arg[i] == '$')
		{
			if (add_new_token(arg, start, i - start, parse))
				define_rule_arg(parse, COMMAND);
			i += manage_key_value(&arg[i], parse, env) - 1;
			start = i;
		}
		if (!arg[i])
			return (-1);
		i++;
	}
	add_new_token(arg, start, i, parse);
	define_rule_arg(parse, COMMAND);
	return (i);
}

static int	manage_simple_quotes(char *arg, t_parse *parse)
{
	int	i;

	i = 1;
	while (arg[i] != '\'')
		i++;
	add_new_token(arg, 1, i - 1, parse);
	define_rule_arg(parse, COMMAND);
	return (i);
}

static int	manage_redi(char *cmd, t_parse *parse)
{
	int	i;

	i = 0;
	while (check_arg(cmd[i]) < 0)
		i++;
	add_new_token(cmd, 0, i, parse);
	return (i - 1);
}

static int	manage_arg(char *cmd, t_parse *parse, int len, t_env *env)
{
	add_new_token(cmd, 0, len, parse);
	if (cmd[len] == '\'')
		len += manage_simple_quotes(&cmd[len], parse);
	else if (cmd[len] == '"')
		len += manage_double_quotes(&cmd[len], parse, env);
	else if (ft_is_whitespace(cmd[len]))
	{
		add_new_token(" ", 0, 1, parse);
		while (ft_is_whitespace(cmd[len]))
			len++;
		return (len);
	}
	else if (cmd[len] == '$')
	{
		if (len == 0 || check_arg(cmd[len - 1]) != -1)
			len = manage_key_value(&cmd[len], parse, env);
		else
			add_new_token(cmd, len, 1, parse);
	}
	else if (check_arg(cmd[len]) < 0)
		len += manage_redi(&cmd[len], parse);
	return (len + 1);
}

static void	print_arg(t_parse *parse)
{
	t_token	*tmp;

	tmp = parse->token;
	printf("\nARG LIST : \n");
	while (tmp)
	{
		printf("%s\n", tmp->arg);
		tmp = tmp->next;
	}
}

t_list	*parse(t_list *lst, char *cmd, t_env *env)
{
	t_parse	parse;
	int		len;
	int		start;

	parse.token = NULL;
	start = 0;
	len = 0;
	while (cmd[len])
	{
		if (check_arg(cmd[len]) != 0)
		{
			len = manage_arg(&cmd[start], &parse, len - start, env);
			len += start;
			start = len;
		}
		else
			len++;
	}
	add_new_token(cmd, start, len, &parse);
	print_arg(&parse);
	//lst = get_commands(lst, &parse);
	return (lst);
}
