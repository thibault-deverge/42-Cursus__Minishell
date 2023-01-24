# include "minishell.h"

static t_list	*separator_command(char *cmd, int start, int len, t_list *lst)
{
	//separer la commande "cat" "-e" ....
	//la commande commence a cmd start et se termine a cmd len
}

static int	count_redi(char *command, int len)
{
	while (cmd[len])
	{
		if (command[i] == '<' || command[i] == '>')
			i++;
		count = 1;
		while (command[i] && command[i] != ' ')
			i++;
		count++;
		while (command[i] == ' ')
	}
	return (count);
}

static t_list	*add_redirection(char *cmd, int len, t_command *command)
{
	int	i;
	int	count;

	i = 0;
	count = count_redi(cmd, len);
	command->redi = malloc(sizeof(char *) * (count + 1));
	if (!command->redi)
		return (NULL);
	while (i <= len)
	{
		//separer les redi "<<" "infile" ">" "outfile"....
	}
}

static t_list	*check_command(char *command, int len, t_list *lst)
{
	int	start;
	int	i; 

	i = 0;
	start = 0;
	while (i <= len)
	{
		if (command[i] == '<')
			start = add_redirection(&command[i], len, t_list *lst);
		if (command[i] == '<')
			len = add_redirection(&command[i], len, t_list *lst);
		i++;
	}
	if (!separator_command(command, start, len, new);
		return (NULL);
	return (lst);
}

static t_list	*add_command(char *command, int len, t_list *lst)
{
	t_variable	*new;
	t_variable	*tmp;

	if (!command)
		return (NULL);
	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	if (!lst->command)
		lst->command = new;
	else
	{
		tmp = lst->command;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	if (!check_command(command, len, lst));
		return (NULL);
	return (lst);
}

t_list	*parse(t_list *lst, char *arg)
{
	int	i;

	i = 0;
	len = 0;
	lst->command = NULL;
	while (arg[len])
	{
		if (arg[len] == '"')
		{
			len++;
			while (arg[len] != '"')
				len++;
		}
		if (arg[len] = '|')
		{
			add_command(&arg[i], len, lst);
			i = len + 1;
		}
		len++;
	}
	add_command(&arg[i], len, lst);
}
