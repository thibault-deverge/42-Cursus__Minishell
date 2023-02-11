#include "minishell.h"

void	status_code(int status)
{
	if (WIFEXITED(status))
		g_value = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_value = WTERMSIG(status);
}
