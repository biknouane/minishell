/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:16:26 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/16 00:10:50 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*expand(char *str, t_list **env_list)
{
	t_list	*node;
	char	*key;
	int		len;
	int		i;
	int 	fdin;
	int		fd[2];
	char	*expanded;
	char	*line;

	pipe(fd);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			while (str[++i] != '\'')
				;
		}
		else if (str[i] == '$')
		{
			printf("+++++++++++++\n");
			++i;
			len = get_key_length(&str[i]);
			key = ft_substr(&str[i], 0, len);
			printf("key :: %s::::\n", key);
			node = find_env(env_list, key);
			if (node)
				printf("key :: %s::::\n", node->value);
			if (node)
				ft_putstr_fd(node->value, fd[1]);
			if (len == 0)
				ft_putchar_fd('$', fd[1]);
			i += len;
			free(key);
		}
		else
			ft_putchar_fd(str[i++], fd[1]);
	}
	close(fd[1]);
	fdin = dup(0);
	dup2(fd[0], 0);
	expanded = NULL;
	while (1)
	{
		line = readline("");
		if (line == NULL)
			break ;
		expanded = ft_strjoin(expanded, line);
	}
	dup2(fdin, 0);
	return (expanded);
}


