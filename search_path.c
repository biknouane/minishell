/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:36:32 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 00:12:54 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for freeing a table of strings
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

// this is function is for cheking all the path 
// variable folders and check if the cmd there
static int	search_in_folders(char **path, char **cmd, char *tmp)
{
	char	*cmd_path;
	int		i;

	i = 0;
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
	return (-1);
}

// this function is for searching for the command is path variable
int	search_cmd(t_list *node, char **cmd)
{
	char	**path;
	char	*tmp;
	char	*ptr;

	ptr = *cmd;
	if (ptr[0] == '/')
	{
		if (access(ptr, X_OK) == 0)
			return (0);
		return (-1);
	}
	tmp = ft_strjoin("/", ptr);
	path = ft_split(node->value, ':');
	search_in_folders(path, cmd, tmp);
	free(tmp);
	free(path);
	return (-1);
}
