/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_holder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:56 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/02 21:04:53 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// parce_cmd ===> parse_pipe ===> parse_redirs ===> parse_exec
// this function is the part of parsing redirections and her_doc 
// and building a node for it
t_command	*parse_redir(t_command *cmd, char **str, char *end_str, char **env_tab)
{
	t_token	token;
	char	*arg;
	char	*end_arg;
	int		fd;

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
			fd = open("/Users/mbiknoua/goinfre/B_HER_KNOU", O_CREAT | O_RDWR | O_TRUNC, 0640);
			// handle if open faild
			//here_doc is here;
			cmd = construct_redir_node(cmd, arg, O_RDONLY, 0);
		}
	}
	return (cmd);
}

// this function is the part of parsing a command and building a node for it
t_command	*parse_exec(char **str, char *end_str, char **env_tab)
{
	t_command	*ret;
	t_exec_cmd	*exec_cmd;
	t_token		token;
	int			arg_count;
	char		*arg;

	ret = construct_exec_node();
	exec_cmd = (t_exec_cmd *) ret;
	arg_count = 0;
	ret = parse_redir(ret, str, end_str, env_tab);
	// look ahead if ther is a pipe then print a syntax error and exit(pipe at the beginnig)
	while (!look_ahead(str, end_str, "|"))
	{
		token = get_token(str, end_str, &arg, NORMAL);
		if (token == 0) // if it is the end of string the we break from the loop
			break ;
		// if (token != WORD) // this is not necessery 
			//panic syntax error
		// exec_cmd->argv = alocate the argement here
		arg_count++;
	}
	return (ret);
}

// this function is the part of parsing a pipe and building a node for it
t_command	*parse_pipe(char **str, char *end_str, char **env_tab)
{
	t_command	*cmd;

	cmd = parse_exec(str, end_str, env_tab);
	if (look_ahead(str, end_str, "|"))
	{
		get_token(str, end_str, 0, 0);
		// check if there is no string and print syntax error and exit(pipe at the end);
		cmd = construct_pipe_node(cmd, parse_pipe(str, end_str));
	}
	return (cmd);
}

// this function is the entry of the parsing functionality
t_command	*parse_cmd(char *str, char **env_tab)
{
	char		*end_str;
	t_command	*cmd;

	end_str = str + ft_strlen(str);
	cmd = parse_pipe(&str, end_str, env_tab);
	look_ahead(&str, end_str, "");
	// if (str != end_str)
		// handel the leftovers
	// nullterminated
	// expand
	return (cmd);
}

// this function is to handle the execution of commands
void	run_cmd(t_command *tree, char **env_tab)
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
		run_cmd(redir_cmd->cmd, env_tab);
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
			run_cmd(pipe_cmd->left_node, env_tab);
		}
		if (fork() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			run_cmd(pipe_cmd->right_node, env_tab);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	exit(0);
}

char	*expand_her_doc(char *str, t_list **env_list)
{
	char	*ptr;
	char	*end;
	char	*tmp;
	t_list	*node;
	char	hold;

	tmp = NULL;
	while (*ptr != '\0' && *ptr != '$')
		ptr++;
	end = ptr;
	end++;
	if (*end != '\n' && *end != '\'' && *end != '"' && *end != ' ' && *end != '\0')
	{
		*ptr = '\0';
		tmp = ft_strjoin(tmp, str);
		ptr++;
		end = ptr;
		while (*end != '\0' && *end != '\'' && *end != '"' && *end != ' ')
			end++;
		hold = *end;
		*end = '\0';
		node = find_env(env_list, ptr);
		if (node)
			tmp = ft_strjoin(tmp, node->value);
		*end = hold;
		tmp = ft_strjoin(tmp, end);
	}
	else
		tmp = str;
	return (tmp);
}

// this function is to handle the expand of env var in her_doc
char	*expand_herdoc(char *line, char **env_list)
{
	char	*new_herdoc;

	new_herdoc = expand_nv_var(line, env_list);
	return (new_herdoc);
}

// this function is to handle reading from stdin and puting the input in a file
void	here_doc(char *eof, int fd, char **env_list)
{
	char	*line;
	int		quote_num;

	// remove quotes from eof
	quote_num = string_quotes(eof);
	// if quote_num is not 0 then this is a syntax error;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, eof))
			break ;
		// expand line
		ft_putendl_fd(line, fd);
	}
}
