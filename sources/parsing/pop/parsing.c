#include "minishell.h"

static void	define_rule_arg(t_parse *parse, int rule)
{
	t_token *tmp;

	tmp = parse->token;
	if (!tmp)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->rule = rule;
}

static int	check_arg(char c)
{
	if (c == '\'' || c == '"' || c == '$' || ft_is_whitespace(c))
		return (1);
	if (c == '>' || c == '<')
		return (-1);
	else if (c == '|')
		return (-2);
	return (0);
}

static void	place_back_token(t_parse *parse, t_token *new)
{
	t_token	*tmp;
	int		index;

	index = 0;
	if (!parse->token)
		parse->token = new;
	else
	{
		tmp = parse->token;
		while (tmp->next)
		{
			tmp = tmp->next;
			index++;
		}
		tmp->next = new;
		tmp->index = index;
	}
}

static t_parse	*add_new_token(char *arg, int start, int len, t_parse *parse)
{
	t_token	*new;
	int		i;

	if (start == len)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->arg = ft_substr(arg, start, len);
	if (!new->arg)
		return (NULL);
	new->next = NULL;
	place_back_token(parse, new);
	i = 0;
	while (new->arg[i])
	{
		if (check_arg(new->arg[i]) < 0)
		{
			define_rule_arg(parse, REDI);
			return (parse);
		}
		i++;
	}
	define_rule_arg(parse, COMMAND);
	return (parse);
}

static char	*get_content_of_key_value(char *key_value, int len, t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (ft_strncmp(key_value, tmp->name, len) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	manage_key_value(char *arg, t_parse *parse, t_env *env)
{
	int		i;
	int		start;
	char	*add_content;
	
	i = 1;
	start = 1;
	while (arg[i] && arg[i] != ' ' && arg[i] != '"')
		i++;
	add_content = get_content_of_key_value(&arg[start], i - start, env);
	if (add_content)
		add_new_token(add_content, 0, ft_strlen(add_content), parse);
	else
		add_new_token(arg, 0, i, parse);
	return (i);
}

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
			if (add_new_token(arg, start, i, parse))
				define_rule_arg(parse, COMMAND);
//faire un manage key value unique pour les doubles quotes
			i = manage_key_value(&arg[i], parse, env);
			start = i;
		}
		if (!arg[i])
			return (-1);
		i++;
	}
	add_new_token(arg, start, i - 1, parse);
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
		len -= 1;
	}
	else if (cmd[len] == '$')
	{
		if (len == 0 || check_arg(cmd[len - 1]) != -1)
			len = manage_key_value(&cmd[len], parse, env);
		else
			add_new_token(cmd, len, 1, parse);
	}
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
	int	len;
	int	start;

	parse.token = NULL;
	start = 0;
	len = 0;
	while (cmd[len])
	{
		if (check_arg(cmd[len]) > 0)
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
	lst = get_commands(lst, &parse);
	return (lst);
}
