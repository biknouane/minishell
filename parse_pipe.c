/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:51:18 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 20:15:43 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static t_command	*handle_pipe_errors(t_param_holder *params, t_command *cmd)
{
	if (*(params->input) == 0)
	{
		print_error("syntax error near unexpected token `|`");
		params->is_error = 1;
		params->exit_status = 258;
	}
	else if (see_ahead(params->input, "|"))
	{
		print_error("syntax error near unexpected token `|`");
		params->is_error = 1;
		params->exit_status = 258;
	}
	return (cmd);
}

/// @brief this function is the part of parsing a pipe
/// and building a node for it
/// @return tree of commnads to execute
t_command	*parse_pipe(t_param_holder *params)
{
	t_command	*cmd;
	t_exec_cmd	*tmp;

	cmd = parse_exec(params);
	if (params->is_error)
		return (cmd);
	if (look_ahead(params, "|"))
	{
		if (cmd->type == EXEC)
		{
			tmp = (t_exec_cmd *) cmd;
			if (tmp->argv[0] == NULL)
			{
				print_error("syntax error near unexpected token `|`");
				params->is_error = 1;
				params->exit_status = 258;
				return (cmd);
			}
		}
		get_token(params, 0);
		handle_pipe_errors(params, cmd);
		cmd = construct_pipe_node(cmd, parse_pipe(params));
	}
	return (cmd);
}
