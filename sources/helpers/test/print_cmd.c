#include "minishell.h"

static void	print_matrice(char **matrice, int index)
{
	int	i;

	i = 0;
	if (index == 1)
		printf("1: matrice des commands\n");
	if (index == 2)
		printf("1: matrice des redis\n");
	if (!matrice)
	{
		printf("this matrice is empty.\n");
		return ;
	}
	while (matrice[i])
	{
		printf("Index: %d = %s\n", i, matrice[i]);
		i++;
	}
	printf("\n");
}

void	print_cmd(t_list *list_commands)
{
	t_command	*command;

	command = list_commands->first;
	if (!command)
		return ;
	while (command)
	{
		printf("---- NEW NODE ----\n");
		print_matrice(command->cmd, 1);
		print_matrice(command->redi, 2);
		command = command->next;
	}
}
