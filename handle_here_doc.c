/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:33:13 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/12 15:39:15 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function is to handle reading from 
//         stdin and puting the input in a file
/// @param eof the here doc delimiter
/// @param fd the file to write in
/// @param env_list environment variables for expansion
/// @return -1 if there was an error or 0 if success
int	her_doc(char *eof, int fd, t_list *env_list)
{
	char	*line;
	int		quote_num;
	int		single_quote_num;
	int		double_quote_num;

	printf("we are inside the her_doc handler this is eof: %s\n", eof);
	quote_num = strip_string_quotes(eof, &single_quote_num, &double_quote_num);
	printf("this is the eof from her_doc after striping the quotes: %s----%u\n", eof, (unsigned int)*eof);
	if (quote_num % 2)
	{
		print_error("syntax error you need to close quotes");
		return (-1);
	}
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
			expand_her_doc(line, &env_list, fd);
		else
			ft_putendl_fd(line, fd);
		free(line);
	}
	return (0);
}
