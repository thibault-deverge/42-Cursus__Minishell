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
		//exec_echo(lst.first, &env);
		//exec_pwd(lst.first, &env);
		main_execution(&lst, &env);
    free(cmd);
	//	print_cmd(&lst);
	}
	// print_env(&env);
	// print_export(&env);
	rl_clear_history();
	return (0);
}
