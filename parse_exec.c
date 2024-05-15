/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:50:40 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/16 00:06:48 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function is the part of parsing a command
/// and building a node for it
/// @return tree of commmands to execute
t_command	*parse_exec(t_param_holder *params)
{
	t_command	*ret;
	t_command	*tmp;
	t_redir_cmd	*last_node;
	t_exec_cmd	*exec_cmd;
	t_token		token;
	int			arg_count;
	char		*arg;

	tmp = construct_exec_node();
	exec_cmd = (t_exec_cmd *) tmp;
	ret = NULL;
	last_node = NULL;
	arg_count = 0;
	arg = NULL;
	tmp = parse_redir((t_command *)exec_cmd, params);
	if (params->is_error)
		return (tmp);
	if (ret == NULL && tmp->type != EXEC)
	{
		ret = tmp;
		last_node = (t_redir_cmd *) tmp;
		while (last_node->cmd->type != EXEC)
			last_node = (t_redir_cmd *)(last_node->cmd);
	}
	while (!look_ahead(params, "|"))
	{
		token = get_token(params, &arg);
		if (token == 0) // if it is the end of string the we break from the loop
		{
			free(arg);
			break ;
		}
		printf("befor expanding: :::%s:::\n", arg);
		char *ex = expand(arg, &(params->env_list));
		printf("expanded: :%s\n", ex);
		if (strip_string_quotes(arg, NULL, NULL) % 2)
		{
			print_error("syntax error you need to close the quotes");
			free(arg);
			arg = NULL;
			params->is_error = 1;
			return (ret);
		}
		exec_cmd->argv[arg_count] = arg;
		arg_count++;
		arg = NULL;
		tmp = parse_redir((t_command *)exec_cmd, params);
		if (ret == NULL && tmp->type != EXEC)
		{
			ret = tmp;
			last_node = (t_redir_cmd *) tmp;
			while (last_node->cmd->type != EXEC)
				last_node = (t_redir_cmd *)(last_node->cmd);
		}
		else if (ret != NULL && tmp->type != EXEC)
		{
			last_node->cmd = tmp;
			while (last_node->cmd->type != EXEC)
				last_node = (t_redir_cmd *)(last_node->cmd);
		}
		if (params->is_error)
			break ;
	}
	if (ret)
		return (ret);
	else
		return (tmp);
}
