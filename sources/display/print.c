/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmieuzet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:03:26 by pmieuzet          #+#    #+#             */
/*   Updated: 2023/01/23 12:06:16 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_envp(t_env *envp)
{
	t_variable	*tmp;

	tmp = envp->variable;
	printf("env :\n");
	while (tmp)
	{
		if (tmp->content)
			printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}

void	print_export(t_env *envp)
{
	int			index;
	t_variable	*tmp;

	index = 0;
	tmp = envp->variable;
	printf("\nexport :\n");
	while (tmp)
	{
		if (index == tmp->index)
		{
			if (tmp->content)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->content);
			else
				printf("declare -x %s\n", tmp->name);
			tmp = envp->variable;
			index++;
		}
		else
			tmp = tmp->next;
	}
}

