/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:50:40 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 22:09:17 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command	*handle_initial_redir(t_param_holder *params, t_command *exec_cmd)
{
	t_command	*tmp;

	tmp = parse_redir(exec_cmd, params);
	if (params->is_error)
		return (tmp);
	return (tmp);
}

t_command	*setup_ret_and_last_node(t_command *tmp, t_redir_cmd **last_node)
{
	t_command	*ret;

	ret = NULL;
	if (tmp->type != EXEC)
	{
		ret = tmp;
		*last_node = (t_redir_cmd *) tmp;
		while ((*last_node)->cmd->type != EXEC)
			*last_node = (t_redir_cmd *)((*last_node)->cmd);
	}
	return (ret);
}

void	update_ret_and_last_node(t_command **tmp, t_command **ret, \
				t_redir_cmd **last_node)
{
	if (*ret == NULL && (*tmp)->type != EXEC)
	{
		*ret = *tmp;
		*last_node = (t_redir_cmd *) *tmp;
		while ((*last_node)->cmd->type != EXEC)
			*last_node = (t_redir_cmd *)((*last_node)->cmd);
	}
	else if (*ret != NULL && (*tmp)->type != EXEC) 
	{
		(*last_node)->cmd = *tmp;
		while ((*last_node)->cmd->type != EXEC)
			*last_node = (t_redir_cmd *)((*last_node)->cmd);
	}
}

void	parse_arguments(t_param_holder *params, \
		t_exec_cmd *exec_cmd, t_command **tmp, t_command **ret)
{
	t_token	token;

	while (!look_ahead(params, "|"))
	{
		token = get_token(params, &(params->arg));
		if (token == 0)
		{
			free(params->arg);
			break ;
		}
		params->arg = expand(params->arg, params);
		if (params->arg == NULL)
			continue ;
		if (handle_quotes_and_error(params, &(params->arg)))
			return ;
		exec_cmd->argv[(params->arg_count)++] = params->arg;
		params->arg = NULL;
		*tmp = parse_redir((t_command *)exec_cmd, params);
		if (params->is_error)
			return ;
		update_ret_and_last_node(tmp, ret, &(params->last_node));
	}
}

t_command	*parse_exec(t_param_holder *params)
{
	t_command	*ret;
	t_command	*tmp;
	t_exec_cmd	*exec_cmd;

	tmp = construct_exec_node();
	exec_cmd = (t_exec_cmd *) tmp;
	ret = NULL;
	params->last_node = NULL;
	params->arg = NULL;
	params->arg_count = 0;
	tmp = handle_initial_redir(params, (t_command *)exec_cmd);
	if (params->is_error)
		return (tmp);
	ret = setup_ret_and_last_node(tmp, &(params->last_node));
	parse_arguments(params, exec_cmd, &tmp, &ret);
	if (ret)
		return (ret);
	return (tmp);
}
