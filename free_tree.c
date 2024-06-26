/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:31:45 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 20:40:28 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	free_exec_node(t_command *tree)
{
	t_exec_cmd	*exec_node;
	int			i;

	i = 0;
	exec_node = (t_exec_cmd *) tree;
	while ((exec_node->argv)[i])
	{
		free((exec_node->argv)[i]);
		i++;
	}
	free(exec_node->argv);
	free(exec_node);
}

void	free_tree(t_command *tree)
{
	t_redir_cmd	*redir_node;
	t_pipe_cmd	*pipe_node;

	if (tree == NULL)
		return ;
	if (tree->type == EXEC)
		free_exec_node(tree);
	else if (tree->type == REDIR)
	{
		redir_node = (t_redir_cmd *) tree;
		free_tree(redir_node->cmd);
		free(redir_node->file);
		free(redir_node);
	}
	else if (tree->type == PIPE)
	{
		pipe_node = (t_pipe_cmd *) tree;
		free_tree(pipe_node->left_node);
		free_tree(pipe_node->right_node);
		free(pipe_node);
	}
}
