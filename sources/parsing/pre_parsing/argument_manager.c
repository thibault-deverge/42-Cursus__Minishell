/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:49:39 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 17:22:03 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	manage_key_value(char *arg, t_parse *parse, t_env *env)
{
	int		i;
	char	*content;

	i = 1;
	content = NULL;
	if (arg[i] == '?')
	{
		parse = get_exit_value(parse);
		if (!parse)
			return (print_perror() - 1);
		return (i);
	}
	while (arg[i] && ft_isalnum(arg[i]))
		i++;
	if (i > 1)
		content = get_value_of_key(&arg[1], i - 1, env);
	if (content)
		parse = add_new_token(content, 0, ft_strlen(content), parse);
	else if (i == 1)
		parse = add_new_token(arg, 0, 1, parse);
	else if (!ft_isalpha(arg[1]))
		parse = add_new_token(arg, 2, i, parse);
	if (!parse && i != 2)
		return (print_perror() - 1);
	return (i - 1);
}

static int	manage_double_quotes(char *arg, t_parse *parse, t_env *env, int len)
{
	int	i;
	int	start;

	i = 1;
	start = 1;
	while (arg[i] && arg[i] != '"')
	{
		if (arg[i] == '$')
		{
			if (start != i && add_new_token(&arg[start], 0, i - start, parse))
				define_rule_token(parse, COMMAND);
			i += manage_key_value(&arg[i], parse, env) + 1;
			start = i;
		}
		else
			i++;
	}
	if (!arg[i])
		return (-2 - len);
	else if (i == 1 && add_new_token("\0", 0, 1, parse))
		define_rule_token(parse, COMMAND);
	if (add_new_token(arg, start, i, parse))
		define_rule_token(parse, COMMAND);
	return (i);
}

static int	manage_simple_quotes(char *arg, t_parse *parse, int len)
{
	int	i;

	i = 1;
	while (arg[i] && arg[i] != '\'')
		i++;
	if (!arg[i])
		return (-2 - len);
	add_new_token(arg, 1, i, parse);
	if (i == 1)
		add_new_token("\0", 0, 1, parse);
	define_rule_token(parse, COMMAND);
	return (i);
}

static int	manage_redirection(char *cmd, t_parse *parse)
{
	int	i;

	i = 0;
	while (check_argument(cmd[i]) < 0)
		i++;
	add_new_token(cmd, 0, i, parse);
	if (strncmp(cmd, "<<", 2) == 0 && check_argument(cmd[2]) != -1)
	{
		while (ft_is_whitespace(cmd[i]))
			i++;
		if (cmd[i] == '$')
		{
			if (!add_new_token(cmd, i, i + 1, parse))
				return (print_perror() - 1);
			return (i);
		}
	}
	return (i - 1);
}

int	manage_argument(char *cmd, t_parse *parse, int len, t_env *env)
{
	add_new_token(cmd, 0, len, parse);
	if (cmd[len] == '\'')
		len += manage_simple_quotes(&cmd[len], parse, len);
	else if (cmd[len] == '"')
		len += manage_double_quotes(&cmd[len], parse, env, len);
	else if (ft_is_whitespace(cmd[len]))
	{
		add_new_token(" ", 0, 1, parse);
		define_rule_token(parse, SPACEBAR);
		while (ft_is_whitespace(cmd[len]))
			len++;
		return (len);
	}
	else if (cmd[len] == '$')
		len += manage_key_value(&cmd[len], parse, env);
	else if (check_argument(cmd[len]) == -1)
		len += manage_redirection(&cmd[len], parse);
	else if (cmd[len] == '|')
		add_new_token("|", 0, 1, parse);
	if (len == -2)
	{
		print_error(ERROR_QUOTES);
		g_value = 2;
	}
	return (len + 1);
}
