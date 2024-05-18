/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:33:13 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 22:37:38 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sig_init_here(int sig)
{
	(void)sig;
	printf("\n");
	exit(1);
}

static int	check_line_if_eof(char *eof, char *line)
{
	if (ft_strncmp(eof, line, ft_strlen(line)))
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (1);
	}
	return (0);
}

static void	wait_for_here_process(int pid, t_param_holder *params)
{
	waitpid(pid, &(params->exit_status), 0);
	signal(SIGINT, sig_handl);
	update_exit_status(&(params->exit_status));
	params->is_error = params->exit_status;
}

static void	here_doc_while(char *line, char *eof, int fd, \
				t_param_holder *params)
{
	while (1)
	{
		line = readline("> ");
		if (!*eof || !line)
		{
			free(line);
			free(eof);
			break ;
		}
		if (check_line_if_eof(eof, line))
			break ;
		if (params->single_quote_num == 0 && params->double_quote_num == 0)
			expand_her_doc(line, &(params->env_list), fd);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
}

/// @brief this function is to handle reading from 
//         stdin and puting the input in a file
/// @param eof the here doc delimiter
/// @param fd the file to write in
/// @param env_list environment variables for expansion
/// @return -1 if there was an error or 0 if success
int	her_doc(char *eof, int fd, t_param_holder *params)
{
	char	*line;
	int		quote_num;
	int		pid;

	params->double_quote_num = 0;
	params->single_quote_num = 0;
	line = NULL;
	quote_num = strip_string_quotes(eof, &params->single_quote_num, \
				&params->double_quote_num);
	if (quote_num % 2)
	{
		print_error("syntax error you need to close quotes");
		params->exit_status = 258;
		return (-1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, sig_init_here);
		here_doc_while(line, eof, fd, params);
		exit(0);
	}
	wait_for_here_process(pid, params);
	return (free(eof), 0);
}
