/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:50:40 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/09 17:35:42 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function is the part of parsing a command
/// and building a node for it
/// @return tree of commmands to execute
t_command	*parse_exec(t_param_holder *params)
{
	t_command	*ret;
	t_exec_cmd	*exec_cmd;
	t_token		token;
	int			arg_count;
	char		*arg;

	ret = construct_exec_node();
	exec_cmd = (t_exec_cmd *) ret;
	arg_count = 0;
	ret = parse_redir(ret, params);
	// look ahead if ther is a pipe then print a syntax error and exit(pipe at the beginnig)
	while (!look_ahead(params, "|"))
	{
		token = get_token(params, &arg);
		if (token == 0) // if it is the end of string the we break from the loop
			break ;
		// if (token != WORD) // this is not necessery 
			//panic syntax error
		// exec_cmd->argv = alocate the argement here
		arg_count++;
		ret = parse_redir(ret, params);
	}
	return (ret);
}
