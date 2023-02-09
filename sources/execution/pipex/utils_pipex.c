#include "minishell.h"

/*
 * @summary:
 * 		- Free both matrices passed as parameter.
*/
void	free_matrices(char **matrix1, char **matrix2)
{
	free_matrix(matrix1);
	free_matrix(matrix2);
}

/*
 * @summary:
 * 		- Check if the command we are handling is the last one.
*/
int	is_last_command(t_command *command)
{
	if (!command->next)
		return (1);
	return (0);
}

/*
 * @summary:
 * 		- Print errno if parameter 'is_perror' is truthy.
 * 		- Free list of commands and envirornment then exit program.
*/
void	exit_child(t_list *list_cmd, t_env *env, int is_perror, int exit_value)
{
	if (is_perror)
		print_perror();
	free_env(env->var);
	free_matrix(env->envp);
	free_commands(list_cmd->first);
	exit(exit_value);
}

/*
 * @summary:
 * 		- Dup2() the pipes to stdin and stdout depend which
 * 		command we are handling (first, middle or last).
*/
int	make_dup_cmd(int pipes[][2], int idx_cmd)
{
	if (idx_cmd == FIRST_CMD)
	{
		if (dup2(pipes[0][1], STDOUT_FILENO) == -1)
			return (print_perror());
		close_pipe(pipes[0]);
	}
	else
	{
		close(pipes[0][1]);
		if (dup2(pipes[0][0], STDIN_FILENO) == -1)
			return (print_perror());
		close(pipes[0][0]);
		if (idx_cmd == MIDDLE_CMD)
		{
			close(pipes[1][0]);
			if (dup2(pipes[1][1], STDOUT_FILENO) == -1)
				return (print_perror());
			close(pipes[1][1]);
		}
	}
	return (RETURN_SUCCESS);
}

/*
 * @summary: 
 * 		- Join string 's1' and 's2' with the '\' between them.
 * 		- Allow to transform the name of the command to its absolute path.
*/
char	*ft_joinpath(char const *s1, char const *s2)
{
	char			*pt_newstr;
	size_t			s1_len;
	size_t			s2_len;
	size_t			total_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_len = s1_len + s2_len + 1;
	pt_newstr = (char *)malloc(total_len + 1);
	if (!pt_newstr)
		return (NULL);
	ft_strlcpy(pt_newstr, s1, s1_len + 1);
	pt_newstr[s1_len] = '/';
	pt_newstr[s1_len + 1] = '\0';
	ft_strlcat(pt_newstr, s2, total_len + 1);
	return (pt_newstr);
}
