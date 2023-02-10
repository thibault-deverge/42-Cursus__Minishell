#include "minishell.h"

void	status_code(int status)
{
	if (WIFEXITED(status))
		g_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_value = WTERMSIG(status);
}

void	sig_handler(int sig_id)
{
	if (sig_id == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_redisplay();
	}
}
