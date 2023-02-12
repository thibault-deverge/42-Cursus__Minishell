/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:50:04 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/12 20:52:56 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * @summary:
 * 		- Check argument passed as parameter and return a different
 * 		integer depend its type.
*/
int	check_argument(char c)
{
	if (c == '\'' || c == '"' || c == '$' || ft_is_whitespace(c))
		return (1);
	else if (c == '>' || c == '<')
		return (-1);
	else if (c == '|')
		return (-2);
	return (0);
}

/*
 * @summary:
 * 		- Add rule of the token at the last node of the pre-parsing
 * 		linked list.
*/
void	define_rule_token(t_parse *parse, int rule)
{
	t_token	*tmp;

	tmp = parse->token;
	if (!tmp)
		return ;
	while (tmp->next)
		tmp = tmp->next;
	tmp->rule = rule;
}

/*
 * @summary:
 * 		- Get value of a environment variable based on its key and return
 * 		it.
*/
char	*get_value_of_key(char *key, int len, t_env *env)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->name, len) == 0
			&& ft_strncmp(key, tmp->name, ft_strlen(tmp->name)) == 0)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}
