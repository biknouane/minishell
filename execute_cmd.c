/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:46:22 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 01:16:34 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_builting(char *cmd)
{
	if (ft_strcmp("echo", cmd))
		return (1);
	else if (ft_strcmp("export", cmd))
		return (1);
	else if (ft_strcmp("unset", cmd))
		return (1);
	else if (ft_strcmp("cd", cmd))
		return (1);
	else if (ft_strcmp("pwd", cmd))
		return (1);
	else if (ft_strcmp("exit", cmd))
		return (1);
	else if (ft_strcmp("env", cmd))
		return (1);
	return (0);
}
// this function is for executing the command
static void	execute_exec_node(t_command *tree, t_list **env_list, int is_pipe)
{
	t_exec_cmd	*exec_cmd;
	int			ret;
	int			pid;
	int			exit_status;

	exec_cmd = (t_exec_cmd *) tree;
	if (exec_cmd->argv[0] == 0)
		return ;
	if (is_builting(exec_cmd->argv[0]))
	{
		ret = handle_builtin(exec_cmd->argv[0], exec_cmd->argv, env_list);
		return ;
	}
	if (search_cmd(find_env(env_list, "PATH"), &(exec_cmd->argv[0])) == -1)
	{
		// set exit status to 127;
		return ;
	}
	if (!is_pipe)
	{
		pid = fork();
		if (pid == 0)
		{
			execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(env_list));
			perror("minishell");
			exit (126);
		}
		wait(&exit_status);
	}
	else
	{
		execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(env_list));
		perror("minishell");
		// set exit status to 126
	}
}

// this function is for handling the redirections
static void	execute_redir_node(t_command *tree, t_list **env_list, \
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
	execute_cmd(redir_cmd->cmd, env_list, exit_status);
}

// this function is for handling the execution of pipes
static void	execute_pipe_node(t_command *tree, t_list **env_list, \
								int *exit_status, int *p)
{
	t_pipe_cmd	*pipe_cmd;

	pipe_cmd = (t_pipe_cmd *) tree;
	// if (pipe(p) < 0)
		// print an errore and exit
	if (fork() == 0)
	{
		dup2(1, p[1]);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->left_node, env_list, exit_status);
	}
	if (fork() == 0)
	{
		dup2(0, p[0]);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->right_node, env_list, exit_status);
	}
	close(p[0]);
	close(p[1]);
	wait(exit_status);
	wait(exit_status);
}

// this function is to handle the execution of commands
void	execute_cmd(t_command *tree, t_list **env_list, int *exit_status)
{
	int			p[2];
	static int	is_pipe;

	if (!tree)
		exit(1);
	if (tree->type == EXEC)
		execute_exec_node(tree, env_list, is_pipe);
	else if (tree->type == REDIR)
		execute_redir_node(tree, env_list, exit_status);
	else if (tree->type == PIPE)
	{
		is_pipe = 1;
		execute_pipe_node(tree, env_list, exit_status, p);
	}
}
