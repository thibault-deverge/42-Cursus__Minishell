#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list	lst;
	char	*cmd;

	(void)argc;
	(void)argv;
	get_env(&env, envp);
	while (1)
	{
		cmd = get_input(&env);
		if (!main_parsing(&lst, cmd, &env))
			continue ;
		if (!heredoc_manager(&lst))
			continue ;
		main_execution(&lst, &env);
    	free(cmd);
		free_commands(lst.first);
		//print_cmd(&lst);
	}
	// print_env(&env);
	// print_export(&env);
	free_env(env.var);
	rl_clear_history();
	return (0);
}
