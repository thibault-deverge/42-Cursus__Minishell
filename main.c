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
		if (!cmd[0] || ft_is_whitespace(cmd[0]))
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
