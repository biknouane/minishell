/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:49:59 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/14 22:43:31 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is the part of parsing redirections and her_doc 
// and building a node for it
t_command	*parse_redir(t_command *cmd, t_param_holder *params)
{
	t_token		token;
	t_redir_cmd	*ret;
	t_redir_cmd	*tmp;
	t_command	*last_node;
	char		*file;
	char		*eof;
	int			fd;
	int			found_redir;

	file = NULL;
	eof = NULL;
	ret = NULL;
	tmp = NULL;
	found_redir = 0;
	while (look_ahead(params, "<>"))
	{
		found_redir = 1;
		token = get_token(params, 0);
		if (token == RE_IN || token == RE_OUT || token == APEND)
		{
			if (get_token(params, &file) != WORD)
			{
				print_error("syntax error file name missing");
				free(file);
				file = NULL;
				params->is_error = 1;
				return (cmd);
			}
			if (token == RE_IN)
			{
				last_node = construct_redir_node(cmd, file, O_RDONLY, 0);
				if (ret == NULL)
					ret = (t_redir_cmd *) last_node;
				else if (ret != NULL && tmp == NULL)
				{
					ret->cmd = last_node;
					tmp = (t_redir_cmd *) last_node;
				}
				else
				{
					tmp->cmd = last_node;
					tmp = (t_redir_cmd *) last_node;
				}
			}
			else if (token == RE_OUT)
			{
				last_node = construct_redir_node(cmd, file, \
							O_RDWR | O_CREAT | O_TRUNC, 1);
				if (ret == NULL)
					ret = (t_redir_cmd *) last_node;
				else if (ret != NULL && tmp == NULL)
				{
					ret->cmd = last_node;
					tmp = (t_redir_cmd *) last_node;
				}
				else
				{
					tmp->cmd = last_node;
					tmp = (t_redir_cmd *) last_node;
				}
			}
			else if (token == APEND)
			{
				last_node = construct_redir_node(cmd, file, \
							O_RDWR | O_CREAT | O_APPEND, 1);
				if (ret == NULL)
					ret = (t_redir_cmd *) last_node;
				else if (ret != NULL && tmp == NULL)
				{
					ret->cmd = last_node;
					tmp = (t_redir_cmd *) last_node;
				}
				else
				{
					tmp->cmd = last_node;
					tmp = (t_redir_cmd *) last_node;
				}
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
				eof = NULL;
				free(file);
				file = NULL;
				return (cmd);
			}
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0640);
			if (her_doc(eof, fd, params->env_list))
			{
				params->is_error = 1;
				unlink(file);
				close(fd);
				free(eof);
				eof = NULL;
				free(file);
				file = NULL;
				return (cmd);
			}
			free(eof);
			eof = NULL;
			close(fd);
			last_node = construct_redir_node(cmd, file, O_RDONLY, 0);
			if (ret == NULL)
				ret = (t_redir_cmd *) last_node;
			else if (ret != NULL && tmp == NULL)
			{
				ret->cmd = last_node;
				tmp = (t_redir_cmd *) last_node;
			}
			else
			{
				tmp->cmd = last_node;
				tmp = (t_redir_cmd *) last_node;
			}
		}
	}
	free(file);
	if (found_redir)
		return ((t_command *) ret);
	return (cmd);
}
