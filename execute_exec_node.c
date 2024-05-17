/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exec_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:21:32 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 18:54:58 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	exec_node_in_pipe(t_param_holder *params, int *fd_in, \
					int *fd_out, t_exec_cmd *exec_cmd)
{
	if (is_builting(exec_cmd->argv[0]))
	{
		if (params->fd_index)
		{
			*fd_in = dup(0);
			*fd_out = dup(1);
			handle_redirections(params);
		}
		exit(handle_builtin(exec_cmd->argv[0], exec_cmd->argv, \
						&(params->env_list)));
	}
	else
	{
		search_cmd(find_env(&(params->env_list), "PATH"), \
					&(exec_cmd->argv[0]));
		if (params->fd_index)
		{
			// fd_in = dup(0);
			// fd_out = dup(1);
			handle_redirections(params);
		}
		execve(exec_cmd->argv[0], exec_cmd->argv, \
				make_env_tab(&(params->env_list)));
		exit (126);
	}
}

static void	exec_builting_in_no_pipe(t_param_holder *params, int *fd_in, \
					int *fd_out, t_exec_cmd *exec_cmd)
{
	if (params->fd_index)
	{
		*fd_in = dup(0);
		*fd_out = dup(1);
		handle_redirections(params);
		params->exit_status = handle_builtin(exec_cmd->argv[0], exec_cmd->argv, \
			&(params->env_list));
		dup2(*fd_in, 0);
		dup2(*fd_out, 1);
		close_open_fds(params);
		close(*fd_in);
		close(*fd_out);
		return ;
	}
	else
	{
		params->exit_status = handle_builtin(exec_cmd->argv[0], exec_cmd->argv, \
				&(params->env_list));
		return ;
	}
}

static void	exec_node_in_no_pipe(t_param_holder *params, int *fd_in, \
					int *fd_out, t_exec_cmd *exec_cmd)
{
	if (is_builting(exec_cmd->argv[0]))
		exec_builting_in_no_pipe(params, fd_in, fd_out, exec_cmd);
	else
		handle_normal_in_no_pipe(params, fd_in, fd_out, exec_cmd);
}

// this function is for executing the command
void	execute_exec_node(t_command *tree, t_param_holder *params)
{
	t_exec_cmd	*exec_cmd;
	int			fd_in;
	int			fd_out;
	int			i;

	exec_cmd = (t_exec_cmd *) tree;
	if (exec_cmd->argv[0] == 0)
	{
		i = 0;
		if (params->fd_index)
		{
			while (i < params->fd_index)
			{
				close(params->files_table[i]);
				i++;
			}
		}
		return ;
	}
	if (params->is_pipe)
		exec_node_in_pipe(params, &fd_in, &fd_out, exec_cmd);
	else
		exec_node_in_no_pipe(params, &fd_in, &fd_out, exec_cmd);
}
