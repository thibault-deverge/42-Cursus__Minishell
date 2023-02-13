#include "minishell.h"

/*
 * @summary:
 * 		- Dupplique stdin and modify signal to handle heredoc case. 
 * 		- If SIGINT is call in a heredoc, it'll close stdin to finish 
 * 		readline() call and then replace stdin as default.
*/
int	set_signal_heredoc(void)
{
	int	stdin_dup;

	stdin_dup = dup(0);
	modify_signals(HEREDOC_SIGNAL);
	return (stdin_dup);
}
