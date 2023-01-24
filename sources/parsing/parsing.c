#include "minishell.h"

static void	manage_double_quotes(char *arg, t_parse *parse, int *start, t_env *envp)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] != '"')
	{
		if (arg[i] == '$')
		{
			len = i + 1;
			while(arg[len] != ' ')
				len++;
			add_
		}
	}
}

static void	manage_simple_quotes()

t_list	*parse(t_list *lst, char *cmd, t_env *envp)
{
	t_parse	parse;
	int		len;
	int		start;

	parse->token = NULL;
	i = 0;
	start = 0;
	while (cmd[len])
	{
		if (cmd[len] == ''')
			len = manage_simple_quotes(&cmd[len]);
		else if (cmd[len] == '"')
			len = manage_quotes(&cmd[len], &parse, &start, envp);
		else if (cmd[len] == ' ' || cmd[len] <= 9 && cmd[len] >= 13)
		{
			len = manage_white_space(&cmd[start], len, &parse);
			start = len;
		}
		len++;
	}
	if (start != len)
		add_new_koten();
	//lst = to_keep_commands(lst, &parse);
}
