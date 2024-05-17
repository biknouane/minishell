/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:46:22 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 15:40:03 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_exit_status(int *exit_status)
{
	unsigned char	*sts;

	sts = (unsigned char *)exit_status;
	if (sts[0])
		*exit_status = sts[0] + 128;
	else
		*exit_status = sts[1];
}

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

void	handle_redirections(t_param_holder *params)
{
	int	i;

	i = 0;
	while (i < params->fd_index)
	{
		dup2(params->files_table[i], params->fd_table[i]);
		i++;
	}
}

void	close_open_fds(t_param_holder *params)
{
	int	i;

	i = 0;
	while (i < params->fd_index)
	{
		close(params->files_table[i]);
		i++;
	}
}

// this function is for executing the command
static void	execute_exec_node(t_command *tree, t_param_holder *params)
{
	t_exec_cmd	*exec_cmd;
	int			pid;
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
	{
		if (is_builting(exec_cmd->argv[0]))
		{
			if (params->fd_index)
			{
				fd_in = dup(0);
				fd_out = dup(1);
				handle_redirections(params);
			}
			exit(handle_builtin(exec_cmd->argv[0], exec_cmd->argv, &(params->env_list)));
		}
		else
		{
			search_cmd(find_env(&(params->env_list), "PATH"), &(exec_cmd->argv[0]));
			if (params->fd_index)
			{
				// fd_in = dup(0);
				// fd_out = dup(1);
				handle_redirections(params);
			}
			execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(&(params->env_list)));
			exit (126);
		}
	}
	else
	{
		if (is_builting(exec_cmd->argv[0]))
		{
			if (params->fd_index)
			{
				fd_in = dup(0);
				fd_out = dup(1);
				handle_redirections(params);
				params->exit_status = handle_builtin(exec_cmd->argv[0], exec_cmd->argv, &(params->env_list));
				dup2(fd_in, 0);
				dup2(fd_out, 1);
				close_open_fds(params);
				close(fd_in);
				close(fd_out);
				return ;
			}
			else
			{
				params->exit_status = handle_builtin(exec_cmd->argv[0], exec_cmd->argv, &(params->env_list));
				return ;
			}
		}
		else
		{
			pid = fork();
			if (pid == 0)
			{
				signal(SIGQUIT, SIG_DFL);
				signal(SIGINT, SIG_DFL);
				search_cmd(find_env(&(params->env_list), "PATH"), &(exec_cmd->argv[0]));
				if (params->fd_index)
				{
					printf("this is the exit status: %d\n", params->exit_status);
					fd_in = dup(0);
					fd_out = dup(1);
					handle_redirections(params);
					execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(&(params->env_list)));
				}
				else
				{
					execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(&(params->env_list)));
				}
				perror("minishell: execve:");
				exit (126);
			}
			if (params->fd_index)
			{
				close_open_fds(params);
				params->fd_index = 0;
			}
			forcked = 1;
			wait(&(params->exit_status));
			forcked = 0;
			update_exit_status(&(params->exit_status));
		}
	}
}

// this function is for handling the redirections
static void	execute_redir_node(t_command *tree, t_param_holder *params)
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
		ft_putstr_fd(": No such file or directory\n", 2);
		params->exit_status = 1;
		return ;
	}
	params->files_table[params->fd_index] = open_fd;
	(params->fd_index)++;
	execute_cmd(redir_cmd->cmd, params);
	return ;
}
// this function is for handling the execution of pipes
static void	execute_pipe_node(t_command *tree, t_param_holder *params, int *p, int *root)
{
	t_pipe_cmd	*pipe_cmd;
	int			pid[2];

	(void)root;
	pipe_cmd = (t_pipe_cmd *) tree;
	if (pipe(p) < 0)
	{
		ft_putstr_fd("error with the pipe\n", 2);
		exit(1);
	}
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
	close(p[0]);
	close(p[1]);
	waitpid(pid[0], &(params->exit_status), 0);
	waitpid(pid[1], &(params->exit_status), 0);
	update_exit_status(&(params->exit_status));
	if (!*root)
		exit(params->exit_status);
}

// this function is to handle the execution of commands
void	execute_cmd(t_command *tree, t_param_holder *params)
{
	int			p[2];
	static int	root;
	static int	already_forked;

	if (!tree)
		exit(1);
	if (tree->type == EXEC)
		execute_exec_node(tree, params);
	else if (tree->type == REDIR)
		execute_redir_node(tree, params);
	else if (tree->type == PIPE)
	{
		if (!root && !already_forked)
		{
			root = 1;
			already_forked = 1;
		}
		else if (root && already_forked)
			root = 0;
		params->is_pipe = 1;
		execute_pipe_node(tree, params, p, &root);
	}
	root = 0;
	already_forked = 0;
}
