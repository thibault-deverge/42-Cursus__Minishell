#include "minishell.h"

/*
 * @summary:
 * 		- Display error message passed via errno variable
 * 		and exit.
*/
static void	throw_perror_prompt(t_env *env)
{
	perror("error");
	free_env(env->var);
	rl_clear_history();
	exit(1);
}

/*
 * @summary:
 * 		- Display error message passed as parameter on STDERR,
 * 		free environment and prompt, clear history and exit.
*/
static void	throw_error_prompt(char *err_msg, char *prompt, t_env *env)
{
	ft_putstr_fd(err_msg, 2);
	free_env(env->var);
	free(prompt);
	rl_clear_history();
	exit(1);
}

/*
 * @summary:
 * 		- Get current working directory and join it with '$'.
 * 		- Join with team's in a way to have a prompt : DREAMTEAM:PWD$
*/
static char	*get_prompt(void)
{
	char	*pwd_env;
	char	pwd_buf[1024];
	char	*custom_prompt;

	if (!getcwd(pwd_buf, PATH_SIZE))
		return (NULL);
	pwd_env = ft_strjoin(pwd_buf, "$ ");
	if (!pwd_env)
		return (NULL);
	custom_prompt = ft_strjoin("DREAMTEAM:", pwd_env);
	free(pwd_env);
	return (custom_prompt);
}

/*
 * @summary:
 * 		- Ask user to enter a prompt and return it.
 * 		- Return NULL if user enter EOF.
*/
char	*get_input(t_env *env)
{
	char	*command;
	char	*prompt;

	prompt = get_prompt();
	if (prompt == NULL)
		throw_perror_prompt(env);
	command = readline(prompt);
	if (!command)
		throw_error_prompt(ERROR_PROMPT, prompt, env);
	if (command[0])
		add_history(command);
	free(prompt);
	return (command);
}
