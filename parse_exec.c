/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:50:40 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 19:40:47 by mbiknoua         ###   ########.fr       */
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
	arg = NULL;
	ret = parse_redir(ret, params);
	if (params->is_error)
		return (ret);
	// if (see_ahead(params->input, "|"))
	// {
	// 	print_error("syntax error: you cant begain with a pipe");
	// 	params->is_error = 1;
	// 	return (ret);
	// }
	// printf("args ::: %s\n", params->input);
	// look ahead if ther is a pipe then print a syntax error and exit(pipe at the beginnig)
	while (!look_ahead(params, "|"))
	{
		token = get_token(params, &arg);
		// printf("args ::: %s\n", arg);
		if (token == 0) // if it is the end of string the we break from the loop
		{
			free(arg);
			break ;
		}
		if (strip_string_quotes(arg, NULL, NULL) % 2)
		{
			// printf("args after ::: %s\n", arg);
			print_error("syntax error you need to close the quotes");
			free(arg);
			// printf("args after ::: %s\n", arg);
			arg = NULL;
			params->is_error = 1;
			return (ret);
		}
		// if (token != WORD) // this is not necessery 
			//panic syntax error
		exec_cmd->argv[arg_count] = arg;
		// printf("^[%d]^^^^%s\n",arg_count , exec_cmd->argv[arg_count]);
		arg_count++;
		arg = NULL;
		ret = parse_redir(ret, params);
		if (params->is_error)
			break ;
	}
	// printf("did i return from exec node creation??????\n");
	return (ret);
}
