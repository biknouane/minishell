/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:51:18 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/11 15:42:56 by mbiknoua         ###   ########.fr       */
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
	printf("returned from the exec parser to pipe parser\n");
	if (params->is_error)
		return (cmd);
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
	if (look_ahead(params, "|"))
	{
		printf("i found the pipe\n");
		get_token(params, 0);
		printf("-----am i here %d\n", *(params->input));
		if (*(params->input) == 0)
		{
			print_error("syntax error: you can't have a pipe at the end");
			return (cmd);
		}
		else if (see_ahead(params->input, "|"))
		{
			print_error("syntax error: you can't have two pipes");
			return (cmd);
		}
		// check if there is no string and 
		//print syntax error and exit(pipe at the end);
		cmd = construct_pipe_node(cmd, parse_pipe(params));
	}
	return (cmd);
}
