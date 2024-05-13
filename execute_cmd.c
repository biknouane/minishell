/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:46:22 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 23:57:24 by mbiknoua         ###   ########.fr       */
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
static void	execute_exec_node(t_command *tree, t_param_holder *params)
{
	t_exec_cmd	*exec_cmd;
	int			ret;
	int			pid;

	exec_cmd = (t_exec_cmd *) tree;
	if (exec_cmd->argv[0] == 0)
		return ;
	if (is_builting(exec_cmd->argv[0]))
	{
		ret = handle_builtin(exec_cmd->argv[0], exec_cmd->argv, &(params->env_list), params->exit_status);
		return ;
	}
	if (search_cmd(find_env(&(params->env_list), "PATH"), &(exec_cmd->argv[0])) == -1)
	{
		// set exit status to 127;
		return ;
	}
	if (!params->is_pipe)
	{
		printf("i am about to fork for this \n");
		pid = fork();
		if (pid == 0)
		{
			execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(&(params->env_list)));
			perror("minishell");
			exit (126);
		}
		wait(params->exit_status);
	}
	else
	{
		printf("i am about to execute the cmd in pipe mode and the cmd is: %s\n", exec_cmd->argv[0]);
		execve(exec_cmd->argv[0], exec_cmd->argv, make_env_tab(&(params->env_list)));
		perror("minishell");
		// set exit status to 126
	}
}

// this function is for handling the redirections
static void	execute_redir_node(t_command *tree, t_param_holder *params)
{
	t_redir_cmd	*redir_cmd;
	int			open_fd;

	redir_cmd = (t_redir_cmd *) tree;
	params->fd_table[params->fd_index] = redir_cmd->fd;
	open_fd = open(redir_cmd->file, redir_cmd->mode);
	params->files_table[params->fd_index] = open_fd;
	printf("this is the file of this process: %s\n", redir_cmd->file);
	if (open_fd < 0)
	{
		// print_error
	}
	printf("this is the file we closed: %d and this is the one we opend in his place: %s\n", redir_cmd->fd, redir_cmd->file);
	execute_cmd(redir_cmd->cmd, params);
}

// this function is for handling the execution of pipes
static void	execute_pipe_node(t_command *tree, t_param_holder *params, int *p)
{
	t_pipe_cmd	*pipe_cmd;

	pipe_cmd = (t_pipe_cmd *) tree;
	if (pipe(p) < 0)
	{
		printf("error with the pipe");
		exit(-1);
	}
	if (fork() == 0)
	{
		dup2(1, p[1]);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->left_node, params);
	}
	if (fork() == 0)
	{
		dup2(0, p[0]);
		close(p[0]);
		close(p[1]);
		execute_cmd(pipe_cmd->right_node, params);
	}
	wait(params->exit_status);
	wait(params->exit_status);
	close(p[0]);
	close(p[1]);
}

// this function is to handle the execution of commands
void	execute_cmd(t_command *tree, t_param_holder *params)
{
	int			p[2];
	// static int	is_pipe;

	// printf("am i at the beginning fo the execute_cmd function?????\n");
	if (!tree)
		exit(1);
	if (tree->type == EXEC)
	{
		printf("am i bout to enter the exec node??????\n");
		execute_exec_node(tree, params);
	}
	else if (tree->type == REDIR)
	{
		printf("did i enterd the exute_cmd for redir?????\n");
		execute_redir_node(tree, params);
	}
	else if (tree->type == PIPE)
	{
		params->is_pipe = 1;
		printf("am i in the pipe execution???????????????\n");
		return ;
		execute_pipe_node(tree, params, p);
	}
}
