#include "minishell.h"

static void	sigint_handler_prompt(int sig_id)
{
	(void)sig_id;
	ft_putchar_fd('\n', 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	sigint_handler_cmd(int sig_id)
{
	(void)sig_id;
	ft_putchar_fd('\n', 1);
	return ;
}

static void	sigkill_handler_cmd(int sig_id)
{
	(void)sig_id;
	ft_putstr_fd("Quit (core dumped)\n", 1);
}

void	modify_signals(int behavior)
{
	if (behavior == PROMPT_SIGNAL)
	{
		signal(SIGINT, &sigint_handler_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (behavior == CMD_SIGNAL)
	{
		signal(SIGINT, &sigint_handler_cmd);
		signal(SIGQUIT, &sigkill_handler_cmd);
	}
	else if (behavior == FORK_SIGNAL)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
	}
}

void	status_code(int status)
{
	if (WIFEXITED(status))
		g_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_value = WTERMSIG(status);
}
