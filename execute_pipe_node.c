/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:03:52 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 14:37:22 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_pipe_failure(int *p, int *root)
{
	if (pipe(p) < 0)
	{
		ft_putstr_fd("error with the pipe\n", 2);
		if (*root)
			return (1);
		exit(1);
	}
	return (0);
}

static void	wait_for_process(int *p, int *pid, int *root, \
				t_param_holder *params)
{
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &(params->exit_status), 0);
	waitpid(pid[1], &(params->exit_status), 0);
	signal(SIGINT, sig_handl);
	update_exit_status(&(params->exit_status));
	if (!*root)
		exit(params->exit_status);
}

static void	sig_fork(int *pid)
{
	signal(SIGINT, SIG_IGN);
	pid[0] = fork();
}

// this function is for handling the execution of pipes
void	execute_pipe_node(t_command *tree, t_param_holder *params, \
				int *p, int *root)
{
	t_pipe_cmd	*pipe_cmd;
	int			pid[2];

	if (check_pipe_failure(p, root))
		return ;
	pipe_cmd = (t_pipe_cmd *) tree;
	sig_fork(pid);
	if (pid[0] == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(p[1], 1);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->left_node, params);
	}
	pid[1] = fork();
	if (pid[1] == 0)
	{
		signal(SIGINT, SIG_DFL);
		dup2(p[0], 0);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->right_node, params);
	}
	wait_for_process(p, pid, root, params);
}
