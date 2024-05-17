/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:51:18 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 12:38:44 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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
		if (*(params->input) == 0)
		{
			print_error("syntax error near unexpected token `|`");
			params->is_error = 1;
			params->exit_status = 258;
			return (cmd);
		}
		else if (see_ahead(params->input, "|"))
		{
			print_error("syntax error near unexpected token `|`");
			params->is_error = 1;
			params->exit_status = 258;
			return (cmd);
		}
		// check if there is no string and 
		//print syntax error and exit(pipe at the end);
		cmd = construct_pipe_node(cmd, parse_pipe(params));
	}
	return (cmd);
}
