/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 23:36:32 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 00:00:20 by mbiknoua         ###   ########.fr       */
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
			free(*cmd);
			*cmd = cmd_path;
			free_table(path);
			return (0);
		}
		free(cmd_path);
		i++;
	}
	free_table(path);
	return (-1);
}

static void	see_if_dir_or_file(char *ptr)
{
	if (is_directory(ptr))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit(126);
	}
	if (access(ptr, X_OK) == 0)
		return ;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(ptr, 2);
	perror(" ");
	if (access(ptr, X_OK) < 0)
		exit (126);
	exit(1);
}

// this function is for searching for the command is path variable
void	search_cmd(t_list *node, char **cmd)
{
	char	*tmp;
	char	*ptr;

	ptr = *cmd;
	if (node == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(1);
	}
	if (ft_strchr(ptr, '/'))
		see_if_dir_or_file(ptr);
	if ((ptr[0] == '.' && ptr[1] == '/') || (ptr[0] == '/'))
		return ;
	tmp = ft_strjoin("/", ptr);
	if (search_in_folders(ft_split(node->value, ':'), cmd, tmp) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ptr, 2);
		ft_putstr_fd(": command not found\n", 2);
		free(tmp);
		exit(127);
	}
	free(tmp);
}
