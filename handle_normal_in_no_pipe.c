/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_normal_in_no_pipe.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:52:03 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 00:32:01 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	handle_normal(t_param_holder *params, int *fd_in, \
					int *fd_out, t_exec_cmd *exec_cmd)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	search_cmd(find_env(&(params->env_list), "PATH"), &(exec_cmd->argv[0]));
	if (params->fd_index)
	{
		*fd_in = dup(0);
		*fd_out = dup(1);
		handle_redirections(params);
		execve(exec_cmd->argv[0], exec_cmd->argv, \
				make_env_tab(&(params->env_list)));
	}
	else
	{
		execve(exec_cmd->argv[0], exec_cmd->argv, \
				make_env_tab(&(params->env_list)));
	}
	perror("minishell: execve:");
	exit (126);
}

void	handle_normal_in_no_pipe(t_param_holder *params, int *fd_in, \
					int *fd_out, t_exec_cmd *exec_cmd)
{
	int	pid;
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		handle_normal(params, fd_in, fd_out, exec_cmd);
	if (params->fd_index)
	{
		close_open_fds(params);
		params->fd_index = 0;
	}
	wait(&(params->exit_status));
	signal(SIGINT, sig_handl);
	update_exit_status(&(params->exit_status));
}
