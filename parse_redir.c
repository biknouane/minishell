/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:49:59 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/09 21:21:34 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is the part of parsing redirections and her_doc 
// and building a node for it
t_command	*parse_redir(t_command *cmd, t_param_holder *params)
{
	t_token	token;
	char	*file;
	char	*eof;
	int		fd;

	while (look_ahead(params, "<>"))
	{
		token = get_token(params, 0);
		if (token == RE_IN || token == RE_OUT || token == APEND)
		{
			// if (get_token(str, end_str, &arg, &end_arg) != 'a')
				// missing file for redirection
			if (get_token(params, &file) != WORD)
			{
				print_error("syntax error file name missing");
				return (NULL);
			}
			if (token == RE_IN)
				cmd = construct_redir_node(cmd, file, O_RDONLY, 0);
			else if (token == RE_OUT)
				cmd = construct_redir_node(cmd, file, \
							O_RDWR | O_CREAT | O_TRUNC, 1);
			else if (token == APEND)
				cmd = construct_redir_node(cmd, file, \
							O_RDWR | O_CREAT | O_APPEND, 1);
		}
		else if (token == H_DOK)
		{
			file = "/Users/mbiknoua/goinfre/B_HER_KNOU";
			if (get_token(params, &eof) != WORD)
			{
				print_error("syntax error eof missing");
				return (NULL);
			}
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0640);
			// handle if open faild
			//here_doc is here;
			if (her_doc(eof, fd, params->env_list))
				return (NULL);
			close(fd);
			cmd = construct_redir_node(cmd, file, O_RDONLY, 0);
		}
	}
	return (cmd);
}
