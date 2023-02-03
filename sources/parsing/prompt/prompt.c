#include "minishell.h"

/*
 * @summary:
 * 		- Clear history of commands, free environment and throw an
 * 		error.
*/
static void	exit_command_empty(void)
{
	rl_clear_history();
	throw_error(ERROR_PROMPT, EXIT_PROMPT);
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
char	*get_input(void)
{
	char	*command;
	char	*prompt;

	prompt = get_prompt();
	if (prompt == NULL)
		throw_perror(EXIT_ALLOC);
	command = readline(prompt);
	if (!command)
		exit_command_empty();
	if (command[0])
		add_history(command);
	free(prompt);
	return (command);
}
