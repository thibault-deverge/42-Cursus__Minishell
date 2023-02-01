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
	return (i - 1);
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
	while (arg[i] && arg[i] != '"')
	{
		if (arg[i] == '$')
		{
			if (start != i && add_new_token(arg, start, i - start, parse))
				define_rule_arg(parse, COMMAND);
			i += manage_key_value(&arg[i], parse, env);
			start = i;
		}
		else
			i++;
	}
	if (!arg[i])
		return (-1);
	add_new_token(arg, start, i, parse);
	define_rule_arg(parse, COMMAND);
	return (i);
}

static int	manage_simple_quotes(char *arg, t_parse *parse)
{
	int	i;

	i = 1;
	while (arg[i] && arg[i] != '\'')
		i++;
	if (!arg[i])
		return (-1);
	add_new_token(arg, 1, i, parse);
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
	if (strncmp(cmd, "<<", 2) == 0 && check_arg(cmd[2]) != -1)
	{
		while (ft_is_whitespace(cmd[i]))
			i++;
		if (cmd[i] == '$')
		{
			add_new_token(cmd, i, i + 1, parse);
			return (i);
		}
	}
	return (i - 1);
}

int	manage_arg(char *cmd, t_parse *parse, int len, t_env *env)
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
		len += manage_key_value(&cmd[len], parse, env);
	else if (check_arg(cmd[len]) < 0)
		len += manage_redi(&cmd[len], parse);
	if (len < 0)
		print_error(ERROR_QUOTES);
	return (len + 1);
}
