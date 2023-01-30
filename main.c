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
		main_parsing(&lst, cmd, &env);
		// execution(&lst, &envp);
		free(cmd);
	}
	// print_envp(&envp);
	// print_export(&envp);
	rl_clear_history();
	return (0);
}
