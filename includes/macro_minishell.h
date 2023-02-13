/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro_minishell.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeverge <tdeverge@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 18:09:00 by tdeverge          #+#    #+#             */
/*   Updated: 2023/02/13 16:36:05 by tdeverge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACRO_MINISHELL_H
# define MACRO_MINISHELL_H

/********************************************************/
/*						ERROR							*/
/********************************************************/
# define ERROR_PROMPT	"exit\n"
# define ERROR_SYNTAX	"error: syntax error near redirection\n"
# define ERROR_PIPE		"error: syntax error near unexpected token '|'\n"
# define ERROR_QUOTES	"error: missing terminating quote character\n"
# define ERROR_CMD_LOST "error: No such file or directory\n"
# define ERROR_ENV		"env: too many arguments\n"
# define ERROR_CD_ARG	"cd: too many arguments\n"
# define ERROR_CD_FILE  "cd: No such file or directory\n"
# define ERROR_CD_HOME  "cd: home directory can't be found\n"
# define ERROR_EXIT_ARG " too many arguments\n"
# define ERROR_EXIT_NUM " numeric argument required\n"
# define ERROR_OPEN_FD	"No such file or directory\n"
# define ERROR_TEST		"command not found\n"
# define ERROR_HEREDOC	" warning: here-document dilimited by end-of-file"
# define ERROR_DIR		"Is a directory\n"
# define ERROR_PERM		"Permission denied\n"
# define INVALID_KEY	"not a valid identifier\n"

/********************************************************/
/*						EXIT							*/
/********************************************************/
# define EXIT_PROMPT	1
# define EXIT_ALLOC		2
# define EXIT_PARSE_CMD 3
# define EXIT_CMD		4
# define EXIT_BUILTIN	5

/********************************************************/
/*						RETURN							*/
/********************************************************/
# define RETURN_FAILURE 0
# define RETURN_SUCCESS 1

/********************************************************/
/*						COMMAND							*/					
/********************************************************/
# define FIRST_CMD		1
# define MIDDLE_CMD		2
# define LAST_CMD		3

/********************************************************/
/*						REDIRECTIONS					*/
/********************************************************/
# define IN				1
# define OUT			2
# define ADD_OUT		3
# define NO_FILE		-1

/********************************************************/
/*						SIGNAL							*/
/********************************************************/
# define PROMPT_SIGNAL	0
# define CMD_SIGNAL		1
# define FORK_SIGNAL	2
# define HEREDOC_SIGNAL 3

/********************************************************/
/*						TOKEN RULE						*/
/********************************************************/
# define COMMAND		0
# define REDI			1
# define SPACEBAR		2
# define PIPE			3

/********************************************************/
/*						PATHS							*/
/********************************************************/
# define PATH_SIZE		1024

#endif
