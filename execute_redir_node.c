/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir_node.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:00:17 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 12:44:49 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_open_file_to_files_table(t_param_holder *params, int open_fd, 
			t_redir_cmd *redir_cmd)
{
	params->files_table[params->fd_index] = open_fd;
	(params->fd_index)++;
	execute_cmd(redir_cmd->cmd, params);
}

// this function is for handling the redirections
void	execute_redir_node(t_command *tree, t_param_holder *params)
{
	t_redir_cmd	*redir_cmd;
	int			open_fd;

	redir_cmd = (t_redir_cmd *) tree;
	params->fd_table[params->fd_index] = redir_cmd->fd;
	open_fd = open(redir_cmd->file, redir_cmd->mode, 0644);
	if (open_fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(redir_cmd->file, 2);
		if (is_directory(redir_cmd->file))
		{
			ft_putstr_fd(": is a directory\n", 2);
			params->exit_status = 126;
		}
		else
		{
			perror(" ");
			params->exit_status = 1;
		}
		if (params->is_pipe)
			exit(params->exit_status);
		return ;
	}
	add_open_file_to_files_table(params, open_fd, redir_cmd);
}
