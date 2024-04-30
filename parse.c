/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:26:25 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/30 01:54:52 by mbiknoua         ###   ########.fr       */
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

t_token	get_token(char	**str, char *end_str, char **str_ret, t_state *state)
{
	char	*tmp;
	char	*next;
	char	*start_token;
	char	*end_token;
	t_token	ret;

	tmp = *str;
	if (*tmp == '"')
		*state = IN_DOUBLE_QUOTE;
	else if (*tmp == '\'')
		*state = IN_SINGL_QUOTE;
	else
		*state = NORMAL;
	if (*state == NORMAL)
	{
		while (tmp < end_str && ft_strchr("\t\r\n\v ", *tmp))
			tmp++;
	}
	if (str_ret)
		start_token = tmp;
	ret = *tmp;
	if (*tmp == 0)
		ret = *tmp;
	else if (*tmp == '|')
	{
		ret = PIP;
		tmp++;
	}
	else if (*tmp == '>')
	{
		ret = RE_OUT;
		tmp++;
		if (*tmp == '>')
		{
			ret = APEND;
			tmp++;
		}
	}
	else if (*tmp == '<')
	{
		ret = RE_IN;
		tmp++;
		if (*tmp == '<')
		{
			ret = H_DOK;
			tmp++;
		}
	}
	else
	{
		ret = WORD;
		parse_string(&tmp, state);
	}
	if (str_ret)
	{
		end_token = tmp;
		*str_ret = ft_substr(start_token, 0, end_token - start_token);
	}
	while (tmp < end_str && ft_strchr("\t\r\n\v ", *tmp))
		tmp++;
	*str = tmp;
	return (ret);
}

int	look_ahead(char **str, char *end_str, char *tokens)
{
	char	*tmp;
	char	*white_space;

	tmp = *str;
	white_space = "\t\r\n\v ";
	while (tmp < end_str && ft_strchr(white_space, *tmp))
		tmp++;
	*str = tmp;
	return (*tmp && ft_strchr(tokens, *tmp));
}
