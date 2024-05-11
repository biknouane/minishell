/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:49:59 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/11 15:47:32 by mbiknoua         ###   ########.fr       */
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

	file = NULL;
	eof = NULL;
	while (look_ahead(params, "<>"))
	{
		printf("am i inside the redir parser\n");
		token = get_token(params, 0);
		printf("this is the token at the parse redir %c\n", token);
		if (token == RE_IN || token == RE_OUT || token == APEND)
		{
			printf("am i here in the re_in re_out append-------??\n");
			if (get_token(params, &file) != WORD)
			{
				print_error("syntax error file name missing");
				free(file);
				file = NULL;
				params->is_error = 1;
				return (cmd);
			}
			printf("am i here in the re_in re_out append=========??\n");
			if (token == RE_IN)
			{
				printf("i am about constructing the re_in node\n");
				cmd = construct_redir_node(cmd, file, O_RDONLY, 0);
			}
			else if (token == RE_OUT)
			{
				printf("i am about constructing the re_out node\n");
				cmd = construct_redir_node(cmd, file, \
							O_RDWR | O_CREAT | O_TRUNC, 1);
				free(file);
			}
			else if (token == APEND)
			{
				printf("i am about constructing the append node\n");
				cmd = construct_redir_node(cmd, file, \
							O_RDWR | O_CREAT | O_APPEND, 1);
			}
		}
		else if (token == H_DOK)
		{
			file = ft_strdup("/Users/mbiknoua/goinfre/B_HER_KNOU");
			if (get_token(params, &eof) != WORD)
			{
				print_error("syntax error eof missing");
				params->is_error = 1;
				free(eof);
				free(file);
				return (cmd);
			}
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0640);
			// handle if open faild
			//here_doc is here;
			if (her_doc(eof, fd, params->env_list))
			{
				params->is_error = 1;
				// close(fd);
				// unlink this file
				// free(eof);
				return (cmd);
			}
			free(eof);
			close(fd);
			cmd = construct_redir_node(cmd, file, O_RDONLY, 0);
			free(file);
			file = NULL;
		}
	}
	printf("ther is no redires in the input so i am out\n");
	return (cmd);
}
