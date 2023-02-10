#include "minishell.h"

unsigned char	g_value = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list	lst;
	char	*cmd;

	(void)argc;
	(void)argv;
	get_env(&env, envp);
	env.envp = NULL;
	while (1)
	{
		modify_signals(PROMPT_SIGNAL);
		cmd = get_input(&env);
		if (is_empty_cmd(cmd))
			continue ;
		if (!main_parsing(&lst, cmd, &env))
			continue ;
		if (!heredoc_manager(&lst))
			continue ;
		main_execution(&lst, &env);
		free(cmd);
		free_commands(lst.first);
	}
	free_env(env.var);
	rl_clear_history();
	return (0);
}
