/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:46:22 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 13:13:30 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is to handle the execution of commands
void	execute_cmd(t_command *tree, t_param_holder *params)
{
	int			p[2];
	static int	root;
	static int	already_forked;

	if (!tree)
		exit(1);
	if (tree->type == EXEC)
		execute_exec_node(tree, params);
	else if (tree->type == REDIR)
		execute_redir_node(tree, params);
	else if (tree->type == PIPE)
	{
		if (!root && !already_forked)
		{
			root = 1;
			already_forked = 1;
		}
		else if (root && already_forked)
			root = 0;
		params->is_pipe = 1;
		execute_pipe_node(tree, params, p, &root);
	}
	root = 0;
	already_forked = 0;
}
