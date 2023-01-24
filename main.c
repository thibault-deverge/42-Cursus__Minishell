#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	env;
	t_list	lst;
	char	*cmd;

	(void)argv;
	if (argc > 1)
		return (1);
	get_env(&env, envp);
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
