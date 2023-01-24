#include "minishell.h"

/*
 * @summary:
 * 		- Search in environment via name of the variable passed as parameter
 * 		and return its content.
*/
char	*get_var_content(t_env *env, char *var_name)
{
	t_variable	*tmp;

	tmp = env->var;
	while (tmp)
	{
		if (tmp->name == var_name)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (0);
}

/*
 * @summary:
 * 		- Search in environment list for USER and PWD variable.
 * 		- Join these in a way to have a prompt : $USER:PWD >
*/
char	*get_prompt(t_env *env)
{
	char	*user_env;
	char	*pwd_env;
	char	*temp_str;
	char	*custom_prompt;

	user_env = ft_strjoin(get_var_content(env, "USER"), ":");
	if (!user_env)
		return (NULL);
	pwd_env = ft_strjoin(get_var_content(env, "PWD"), " >");
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
	command = readline(prompt);
	if (!command)
	{
		rl_clear_history();
		return (NULL);
	}
	add_history(command);
	return (command);
}
