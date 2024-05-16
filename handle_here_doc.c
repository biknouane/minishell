/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:33:13 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/16 19:07:24 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
	int		single_quote_num;
	int		double_quote_num;
	int		pid;

	quote_num = strip_string_quotes(eof, &single_quote_num, &double_quote_num);
	if (quote_num % 2)
	{
		print_error("syntax error you need to close quotes");
		return (-1);
	}
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			line = readline("> ");
			if (!*eof && !*line)
			{
				free(line);
				break ;
			}
			if (ft_strcmp(eof, line))
			{
				if (line)
				{
					free(line);
					line = NULL;
				}
				break ;
			}
			if (single_quote_num == 0 && double_quote_num == 0)
				expand_her_doc(line, &(params->env_list), fd);
			else
				ft_putendl_fd(line, fd);
			free(line);
		}
		exit(0);
	}
	forcked = 1;
	waitpid(pid, &(params->exit_status), 0);
	forcked = 0;
	update_exit_status(&(params->exit_status));
	return (0);
}
