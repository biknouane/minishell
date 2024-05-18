/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:16:26 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 01:37:46 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	get_key_value(char *str, int fd, t_param_holder *params)
{
	int		i;
	char	*key;
	t_list	*node;
	int		len;

	i = 1;
	if (str[i] == '?')
	{
		ft_putnbr_fd(params->exit_status, fd);
		return (2);
	}
	len = get_key_length(&str[i]);
	key = ft_substr(&str[i], 0, len);
	node = find_env(&(params->env_list), key);
	if (node)
		ft_putstr_fd(node->value, fd);
	if (len == 0)
		ft_putchar_fd('$', fd);
	free(key);
	return (len + 1);
}

int	handle_single_quote(char *str, int fd)
{
	int	i;

	i = 1;
	ft_putchar_fd('\'', fd);
	while (str[i] != '\'' && str[i])
		ft_putchar_fd(str[i++], fd);
	if (str[i] == '\'')
		ft_putchar_fd('\'', fd);
	++i;
	return (i);
}

int	handle_double_quote(char *str, int fd, t_param_holder *params)
{
	int	i;

	ft_putchar_fd('"', fd);
	i = 1;
	while (str[i] != '"' && str[i])
	{
		if (str[i] == '$')
			i += get_key_value(&str[i], fd, params);
		else
			ft_putchar_fd(str[i++], fd);
	}
	if (str[i] == '"')
		ft_putchar_fd('"', fd);
	++i;
	return (i);
}

char	*get_expanded(int fd)
{
	char	*expanded;
	char	*trimed;
	char	*line;

	line = NULL;
	expanded = NULL;
	trimed = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		trimed = ft_strtrim(line, "\n");
		expanded = ft_strjoin(expanded, trimed);
		free(line);
		free(trimed);
	}
	close (fd);
	return (expanded);
}

char	*expand(char *str, t_param_holder *params)
{
	int		i;
	int		fd[2];

	if (!ft_strchr(str, '$'))
		return (str);
	pipe(fd);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			i += handle_single_quote(&str[i], fd[1]);
		if (str[i] == '"')
			i += handle_double_quote(&str[i], fd[1], params);
		else if (str[i] == '$')
			i += get_key_value(&str[i], fd[1], params);
		else
			ft_putchar_fd(str[i++], fd[1]);
	}
	close(fd[1]);
	return (free(str), get_expanded(fd[0]));
}
