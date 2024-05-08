/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:46:22 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 12:31:38 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for executing the command
static void	execute_exec_node(t_command *tree, char **env_tab)
{
	t_exec_cmd	*exec_cmd;

	exec_cmd = (t_exec_cmd *) tree;
	// if (exec_cmd->argv[0] == 0)
	// 	exit(1);
	execve(exec_cmd->argv[0], exec_cmd->argv, env_tab);
	// if execve returns that's mean that it fails and the program is not valid
	// and exit
}

// this function is for handling the redirections
static void	execute_redir_node(t_command *tree, char **env_tab, \
								int *exit_status)
{
	t_redir_cmd	*redir_cmd;

	redir_cmd = (t_redir_cmd *) tree;
	close(redir_cmd->fd);
	if (open(redir_cmd->file, redir_cmd->mode) < 0)
	{
		// print that the open is faild 
		// exit()
	}
	execute_cmd(redir_cmd->cmd, env_tab, exit_status);
}

// this function is for handling the execution of pipes
static void	execute_pipe_node(t_command *tree, char **env_tab, \
								int *exit_status, int *p[])
{
	t_pipe_cmd	*pipe_cmd;

	pipe_cmd = (t_pipe_cmd *) tree;
	// if (pipe(p) < 0)
		// print an errore and exit
	if (fork() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->left_node, env_tab, exit_status);
	}
	if (fork() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->right_node, env_tab, exit_status);
	}
	close(p[0]);
	close(p[1]);
	wait(exit_status);
	wait(exit_status);
}

// this function is to handle the execution of commands
void	execute_cmd(t_command *tree, char **env_tab, int *exit_status)
{
	int			p[2];

	if (!tree)
		exit(1);
	if (tree->type == EXEC)
		execute_exec_node(tree, env_tab);
	else if (tree->type == REDIR)
		execute_redir_node(tree, env_tab, exit_status);
	else if (tree->type == PIPE)
		execute_pipe_node(tree, env_tab, exit_status, &p);
	// exit(0);
}
