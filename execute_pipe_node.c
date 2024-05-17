/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:03:52 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 18:15:29 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	check_pipe_failure(int *p)
{
	if (pipe(p) < 0)
	{
		ft_putstr_fd("error with the pipe\n", 2);
		exit(1);
	}
}

static void	wait_for_process(int *p, int *pid, int *root, \
				t_param_holder *params)
{
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &(params->exit_status), 0);
	waitpid(pid[1], &(params->exit_status), 0);
	update_exit_status(&(params->exit_status));
	if (!*root)
		exit(params->exit_status);
}

// this function is for handling the execution of pipes
void	execute_pipe_node(t_command *tree, t_param_holder *params, \
				int *p, int *root)
{
	t_pipe_cmd	*pipe_cmd;
	int			pid[2];

	check_pipe_failure(p);
	pipe_cmd = (t_pipe_cmd *) tree;
	pid[0] = fork();
	if (pid[0] == 0)
	{
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->left_node, params);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->right_node, params);
	}
	wait_for_process(p, pid, root, params);
}
