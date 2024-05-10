/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:31:45 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/11 00:06:52 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_tree(t_command *tree)
{
	t_exec_cmd	*exec_node;
	t_redir_cmd	*redir_node;
	t_pipe_cmd	*pipe_node;
	int			i;

	if (tree == NULL)
		return ;
	if (tree->type == EXEC)
	{
		i = 0;
		printf("do i have a exec node\n");
		exec_node = (t_exec_cmd *) tree;
		printf("%d---%s\n", i, (exec_node->argv[i]));
		while ((exec_node->argv)[i])
		{
			printf("-----free argv[%d]\n", i);
			free((exec_node->argv)[i]);
			i++;
		}
		printf("did i free the table\n");
		free(exec_node->argv);
		free(exec_node);
	}
	else if (tree->type == REDIR)
	{
		printf("do i have redir node\n");
		redir_node = (t_redir_cmd *) tree;
		free_tree(redir_node->cmd);
		printf("----------\n");
		printf("%s\n", redir_node->file);
		unlink(redir_node->file);
		// free(redir_node->file);
		free(redir_node);
	}
	else if (tree->type == PIPE)
	{
		printf("do i have a pipe nodi\n");
		pipe_node = (t_pipe_cmd *) tree;
		free_tree(pipe_node->left_node);
		printf("//// going to free the right node\n");
		free_tree(pipe_node->right_node);
		free(pipe_node);
	}
}
