/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:36:32 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/01 23:37:00 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_table(char **table)
{
	int	i;

	i = 0;
	if (!table)
		return ;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}

int	search_cmd(t_list *node, char **cmd)
{
	char	**path;
	char	*cmd_path;
	char	*tmp;
	char	*ptr;
	int		i;

	ptr = *cmd;
	if (ptr[0] == '/')
	{
		if (access(ptr, X_OK) == 0)
			return (0);
		return (-1);
	}
	i = 0;
	tmp = ft_strjoin("/", ptr);
	path = ft_split(node->value, ':');
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], tmp);
		if (access(cmd_path, X_OK) == 0)
		{
			*cmd = cmd_path;
			free(tmp);
			free_table(path);
			return (0);
		}
		free(path[i]);
		i++;
	}
	free(tmp);
	free(path);
	return (-1);
}