/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:51:18 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/09 13:30:27 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function is the part of parsing a pipe
/// and building a node for it
/// @return tree of commnads to execute
t_command	*parse_pipe(t_param_holder *params)
{
	t_command	*cmd;

	cmd = parse_exec(params);
	if (look_ahead(params, "|"))
	{
		get_token(params, 0);
		// check if there is no string and 
		//print syntax error and exit(pipe at the end);
		cmd = construct_pipe_node(cmd, parse_pipe(params));
	}
	return (cmd);
}
