#include "minishell.h"

void	define_rule_arg(t_parse *parse, int rule)
{
	t_token	*tmp;

	tmp = parse->token;
	if (!tmp)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->rule = rule;
}

int	check_arg(char c)
{
	if (c == '\'' || c == '"' || c == '$' || ft_is_whitespace(c))
		return (1);
	else if (c == '>' || c == '<')
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

t_parse	*add_new_token(char *arg, int start, int len, t_parse *parse)
{
	t_token	*new;
	int		i;

	if (start == len)
		return (NULL);
	new = malloc(sizeof(t_token));
	new->arg = ft_substr(arg, start, len - start);
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

char	*get_value_of_key(char *key, int len, t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->name, len) == 0 && ft_strncmp(key, tmp->name, ft_strlen(tmp->name) == 0))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
