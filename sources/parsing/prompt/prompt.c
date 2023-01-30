#include "minishell.h"

/*
 * @summary:
 * 		- Clear history of commands, free environment and throw an
 * 		error.
*/
static void	exit_command_empty(t_env *env)
{
	rl_clear_history();
	free_env(env->var);
	throw_error(ERROR_PROMPT, EXIT_PROMPT);
}

/*
 * @summary:
 * 		- Search in environment list for USER and PWD variable.
 * 		- Join these in a way to have a prompt : $USER:PWD >
*/
static char	*get_prompt(t_env *env)
{
	char	*user_env;
	char	*pwd_env;
	char	*custom_prompt;

	user_env = ft_strjoin(get_var_content(env, "USER"), ":");
	if (!user_env)
		return (NULL);
	pwd_env = ft_strjoin(get_var_content(env, "PWD"), "$ ");
	if (!pwd_env)
	{
		free(user_env);
		return (NULL);
	}
	custom_prompt = ft_strjoin(user_env, pwd_env);
	free(user_env);
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

	prompt = get_prompt(env);
	if (prompt == NULL)
	{
		free_env(env->var);
		throw_perror(EXIT_ALLOC);
	}
	command = readline(prompt);
	if (!command)
		exit_command_empty(env);
	if (command[0])
		add_history(command);
	free(prompt);
	return (command);
}
