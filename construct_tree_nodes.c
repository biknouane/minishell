/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct_tree_nodes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:43:57 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 21:31:26 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for constructing the execute node
t_command	*construct_exec_node(void)
{
	t_exec_cmd	*command;

	command = ft_calloc(1, sizeof(t_exec_cmd));
	command->argv = ft_calloc(100, sizeof(char *));
	command->type = EXEC;
	return ((t_command *) command);
}

// this function is for constructing the redirections node
t_command	*construct_redir_node(t_command *sub_node, \
						char *file_name, int mode, int fd)
{
	t_redir_cmd	*command;

	command = ft_calloc(1, sizeof(t_redir_cmd));
	command->type = REDIR;
	command->file = ft_strdup(file_name);
	command->mode = mode;
	command->fd = fd;
	command->cmd = sub_node;
	return ((t_command *) command);
}

// this function is for constructing the pipe node
t_command	*construct_pipe_node(t_command *left_node, t_command *right_node)
{
	t_pipe_cmd	*command;

	command = ft_calloc(1, sizeof(t_pipe_cmd));
	command->type = PIPE;
	command->left_node = left_node;
	command->right_node = right_node;
	return ((t_command *) command);
}
