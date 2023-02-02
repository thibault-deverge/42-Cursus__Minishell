#include "minishell.h"

static int	ft_open(char *file)
{
	
}

int *manage_redi(char **redirections)
{
	int	i;
	int	index[2];

	index[0] = 0;
	index[1] = 0;
	i = 0;
	while (redirections[i])
	{
		if (ft_strcmp(redirections[i], "<") == 0)
		else if (ft_strcmp(redirections[i], "<<") == 0)
			//index = heredoc(redirections[i + 1]);
		else if (ft_strcmp(redirections[i], ">") == 0)
		else if (ft_strcmp(redirections[i], ">>") == 0)
	}
}
