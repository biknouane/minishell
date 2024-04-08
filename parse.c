/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:26:25 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/04 01:42:01 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_command	*construct_exec_node(void)
{
	t_exec_cmd	*command;

	command = ft_calloc(1, sizeof(t_command));
	command->type = EXEC;
	return ((t_command *) command);
}

t_command	*construct_redir_node(t_command *sub_node, \
						char *file, int mode, int fd)
{
	t_redir_cmd	*command;

	command = ft_calloc(1, sizeof(t_redir_cmd));
	command->type = REDIR;
	command->file = file;
	command->mode = mode;
	command->fd = fd;
	command->cmd = sub_node;
	return ((t_command *) command);
}

t_command	*construct_pipe_node(t_command *left_node, t_command *right_node)
{
	t_pipe_cmd	*command;

	command = ft_calloc(1, sizeof(t_pipe_cmd));
	command->type = PIPE;
	command->left_node = left_node;
	command->right_node = right_node;
	return ((t_command *) command);
}

int	get_token(char	**str, char *end_str, char **start_token, char **end_token)
{
	char	*tmp;
	char	*white_space;
	char	*symbols;
	int		ret;

	tmp = *str;
	white_space = "\t\r\n\v";
	symbols = "<|>";
	while (tmp < end_str && ft_strchr(white_space, *tmp))
		tmp++;
	if (start_token)
		*start_token = tmp;
	ret = *tmp;
	if (*tmp == '|')
		tmp++;
	else if (*tmp == '>')
	{
		tmp++;
		if (*tmp == '>')
		{
			ret = '+';
			tmp++;
		}
	}
	else if (*tmp == '<')
	{
		tmp++;
		if (*tmp == '<')
		{
			ret = '-';
			tmp++;
		}
	}
	else
	{
		ret = 'a';
		while (tmp < end_str && !ft_strchr(white_space, *tmp) && \
				!ft_strchr(symbols, *tmp))
			tmp++;
	}
	if (end_token)
		*end_token = tmp;
	while (tmp < end_str && ft_strchr(white_space, *tmp))
		tmp++;
	*str = tmp;
	return (ret);
}

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
// parse_pipe ===> parse_redirs ===> parse_exec