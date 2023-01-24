/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmieuzet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:02:02 by pmieuzet          #+#    #+#             */
/*   Updated: 2023/01/24 09:49:52 by pmieuzet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	envp;
	t_list	lst;
	char	*cmd;

	(void)argv;
	if (argc > 1)
		return (1);
	get_envp(&envp, env);
	cmd = readline(">");
	while (cmd)
	{
		//parse(&lst, cmd, &envp);
		//execution(&lst, &envp);
		free(cmd);
		cmd = readline(">");
	}
	free(cmd);
	//print_envp(&envp);
	//print_export(&envp);
}
