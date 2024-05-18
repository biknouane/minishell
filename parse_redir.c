/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:49:59 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 22:29:09 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	append_redir_cmd(t_redir_cmd **ret, \
	t_redir_cmd **tmp, t_command *last_node)
{
	if (*ret == NULL)
		*ret = (t_redir_cmd *) last_node;
	else if (*ret != NULL && *tmp == NULL)
	{
		(*ret)->cmd = last_node;
		*tmp = (t_redir_cmd *) last_node;
	}
	else
	{
		(*tmp)->cmd = last_node;
		*tmp = (t_redir_cmd *) last_node;
	}
}

int	handle_heredoc_redirection(t_redir_cmd **ret, t_redir_cmd **tmp, \
	t_command *cmd, t_param_holder *params)
{
	t_command	*last_node;
	char		*file;
	int			fd;

	file = ft_strdup("/tmp/B_HER_KNOU");
	if (get_token(params, &(params->eof)) != WORD)
	{
		print_error("syntax error near unexpected token `newline`");
		params->is_error = 1;
		params->exit_status = 258;
		free(file);
		return (0);
	}
	fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0640);
	if (her_doc(params->eof, fd, params))
	{
		params->is_error = 1;
		unlink(file);
		return (free(file), close(fd), 0);
	}
	close(fd);
	last_node = construct_redir_node(cmd, file, O_RDONLY, 0);
	append_redir_cmd(ret, tmp, last_node);
	free(file);
	return (1);
}

int	handle_file_redirection(t_redir_cmd **ret, t_redir_cmd **tmp, \
		t_command *cmd, t_param_holder *params)
{
	t_command	*last_node;

	if (get_token(params, &(params->file)) != WORD)
	{
		print_error("syntax error near unexpected token `newline`");
		params->is_error = 1;
		params->exit_status = 258;
		return (0);
	}
	if (strip_string_quotes(params->file, NULL, NULL) % 2)
	{
		print_error("minishell: syntax error you need to close quotes");
		params->is_error = 1;
		params->exit_status = 258;
		return (0);
	}
	last_node = construct_redir_node(cmd, params->file, \
		get_file_flags(params->token), params->token != RE_IN);
	if (*ret == NULL)
		*ret = (t_redir_cmd *)last_node;
	else
		append_redir_cmd(ret, tmp, last_node);
	return (1);
}

int	process_redirection(t_redir_cmd **ret, t_redir_cmd **tmp, \
		t_command *cmd, t_param_holder *params)
{
	params->token = get_token(params, 0);
	if (params->token == RE_IN || params->token == RE_OUT || \
			params->token == APEND)
		return (handle_file_redirection(ret, tmp, cmd, params));
	else if (params->token == H_DOK)
		return (handle_heredoc_redirection(ret, tmp, cmd, params)); 
	return (1);
}

t_command	*parse_redir(t_command *cmd, t_param_holder *params)
{
	t_redir_cmd	*ret;
	t_redir_cmd	*tmp;
	int			found_redir;

	ret = NULL;
	tmp = NULL;
	found_redir = 0;
	params->file = NULL;
	params->eof = NULL;
	while (look_ahead(params, "<>"))
	{
		found_redir = 1;
		if (!process_redirection(&ret, &tmp, cmd, params))
		{
			free_resources(params->file, params->eof);
			return (cmd);
		}
		free(params->file);
		params->file = NULL;
	}
	free(params->file);
	if (found_redir)
		return ((t_command *)ret);
	return (cmd);
}
