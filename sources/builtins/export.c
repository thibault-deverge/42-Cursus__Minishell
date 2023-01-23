/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmieuzet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:29:05 by pmieuzet          #+#    #+#             */
/*   Updated: 2023/01/23 12:15:51 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static void	check_variable(t_env *envp)
{
	t_variable	*tmp_command;
	t_variable	*tmp_env;

	tmp_command = envp->variable;
	tmp_env = envp->variable;
	while (tmp_command->next)
		tmp_command = tmp_command->next;
	while (tmp_command->content && tmp_env->next)
	{
		if (tmp_env->content && ft_strncmp(tmp_command->content, tmp_env->name,
				ft_strlen(tmp_command->content) + 1) == 0)
		{
			free(tmp_command->content);
			tmp_command->content = ft_substr(tmp_env->content, 0, ft_strlen(tmp_env->content));
		}
		tmp_env = tmp_env->next;
	}
}*/

void	export(char *cmd, t_env *envp)
{
	if (!cmd)
		print_export(envp);
	else
	{
		//check_variable(cmd, envp);
		add_variable(envp, cmd);
		init_ascii_index(envp);
		//check_variable(envp);
	}
}
