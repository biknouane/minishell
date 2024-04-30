/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_holder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:56 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/30 01:56:06 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	look_ahead(char **str, char *end_str, char *tokens)
{
	char	*tmp;
	char	*white_space;

	tmp = *str;
	white_space = "\t\r\n\v";
	while (tmp < end_str && ft_strchr(white_space, *tmp))
		tmp++;
	*str = tmp;
	return (*tmp && ft_strchr(tokens, *tmp));
}

// parce_cmd ===> parse_pipe ===> parse_redirs ===> parse_exec

t_command	*parse_redir(t_command *cmd, char **str, char *end_str)
{
	t_token	token;
	char	*arg;
	char	*end_arg;

	while (look_ahead(str, end_str, "<>"))
	{
		token = get_token(str, end_str, 0, 0);
		// if (get_token(str, end_str, &arg, &end_arg) != 'a')
			// missing file for redirection
		if (token == RE_IN)
			cmd = construct_redir_node(cmd, arg, O_RDONLY, 0);
		else if (token == RE_OUT)
			cmd = construct_redir_node(cmd, arg, \
						O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token == APEND)
			cmd = construct_redir_node(cmd, arg, O_WRONLY | O_CREAT, 1);
		else if (token == H_DOK)
		{
			//here_doc is here;
			cmd = construct_redir_node(cmd, arg, O_RDONLY, 0);
		}
	}
	return (cmd);
}

t_command	*parse_exec(char **str, char *end_str)
{
	t_command	*ret;
	t_exec_cmd	*exec_cmd;
	t_token		token;
	int			arg_count;
	char		*arg;
	char		*end_arg;

	ret = construct_exec_node();
	exec_cmd = (t_exec_cmd *) ret;
	arg_count = 0;
	ret = parse_redir(ret, str, end_str);
	// look ahead if ther is a pipe then print a syntax error and exit(pipe at the beginnig)
	while (!look_ahead(str, end_str, "|"))
	{
		token = get_token(str, end_str, arg, end_arg);
		if (token == 0) // if it is the end of string the we break from the loop
			break ;
		// if (token != WORD) // this is not necessery 
			//panic syntax error
		// exec_cmd->argv = alocate the argement here
		arg_count++;
	}
	return (ret);
}

t_command	*parse_pipe(char **str, char *end_str)
{
	t_command	*cmd;

	cmd = parse_exec(str, end_str);
	if (look_ahead(str, end_str, "|"))
	{
		get_token(str, end_str, 0, 0);
		// check if there is no string and print syntax error and exit(pipe at the end);
		cmd = construct_pipe_node(cmd, parse_pipe(str, end_str));
	}
	return (cmd);
}

t_command	*parse_cmd(char *str)
{
	char		*end_str;
	t_command	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parse_pipe(&str, end_str);
	look_ahead(&str, end_str, "");
	// if (str != end_str)
		// handel the leftovers
	// nullterminated
	// expand
	return (cmd);
}

void	run_cmd(t_command *tree)
{
	int			p[2];
	t_exec_cmd	*exec_cmd;
	t_redir_cmd	*redir_cmd;
	t_pipe_cmd	*pipe_cmd;

	if (!tree)
		exit(1);
	if (tree->type == EXEC)
	{
		exec_cmd = (t_exec_cmd *) tree;
		// if (exec_cmd->argv[0] == 0)
		// 	exit(1);
		execve(exec_cmd->argv[0], exec_cmd->argv, env_tab);
		// if execve returns that's mean that it fails and the program is not valid
		// and exit
	}
	else if (tree->type == REDIR)
	{
		redir_cmd = (t_redir_cmd *) tree;
		close(redir_cmd->fd);
		if (open(redir_cmd->file, redir_cmd->mode) < 0)
		{
			// print that the open is faild 
			// exit()
		}
		run_cmd(redir_cmd->cmd);
	}
	else if (tree->type == PIPE)
	{
		pipe_cmd = (t_pipe_cmd *) tree;
		// if (pipe(p) < 0)
			// print an errore and exit
		if (fork() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			run_cmd(pipe_cmd->left_node);
		}
		if (fork() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			run_cmd(pipe_cmd->right_node);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	exit(0);
}
