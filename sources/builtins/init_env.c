/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmieuzet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:29:11 by pmieuzet          #+#    #+#             */
/*   Updated: 2023/01/23 12:14:04 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_ascii_index(t_env *envp)
{
	t_variable	*tmp_env;
	t_variable	*tmp_var;
	int	i;

	tmp_var = envp->variable;
	tmp_env = envp->variable;
	while (tmp_var->next)
		tmp_var = tmp_var->next;
	while (tmp_env != tmp_var)
	{
		i = 0;
		while (tmp_var->name[i] && tmp_env->name[i]
				&& tmp_var->name[i] == tmp_env->name[i])
			i++;
		if (!tmp_env->name[i] || tmp_var->name[i] - 48 > tmp_env->name[i] - 48)
			tmp_var->index += 1;
		else
			tmp_env->index += 1;
		tmp_env = tmp_env->next;
	}
}

static t_variable	*to_fill_env_variable(t_variable *var, char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	var->name = ft_substr(str, 0, i);
	if (!var->name)
		return (NULL);
	if (i == ft_strlen(str))
		var->content = NULL;
	else
	{
		var->content = ft_substr(str, i + 1, ft_strlen(str));
		if (!var->content)
			return (NULL);
	}
	return (var);
}

t_env	*add_variable(t_env *envp, char *str)
{
	t_variable	*new;
	t_variable	*tmp;

	new = malloc(sizeof(t_variable));
	if (!new)
		return (NULL);
	new = to_fill_env_variable(new, str);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->index = 0;
	if (!envp->variable)
		envp->variable = new;
	else
	{
		tmp = envp->variable;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (envp);
}

void	get_envp(t_env *envp, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		envp = add_variable(envp, env[i]);
		if (!envp)
		{
			//free all
			return ;
		}
		init_ascii_index(envp);
		i++;
	}
}
