/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:51:18 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/16 17:13:51 by mbiknoua         ###   ########.fr       */
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
				print_error("syntax error: you cant begain with a pipe");
				params->is_error = 1;
				return (cmd);
			}
		}
		get_token(params, 0);
		if (*(params->input) == 0)
		{
			print_error("syntax error: you can't have a pipe at the end");
			params->is_error = 1;
			return (cmd);
		}
		else if (see_ahead(params->input, "|"))
		{
			print_error("syntax error: you can't have two pipes");
			params->is_error = 1;
			return (cmd);
		}
		// check if there is no string and 
		//print syntax error and exit(pipe at the end);
		cmd = construct_pipe_node(cmd, parse_pipe(params));
	}
	return (cmd);
}
