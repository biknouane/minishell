/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:36:20 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/12 23:43:01 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this is the alternative of execve of builtings
int	handle_builtin(char	*cmd, char **args, t_list **env_list)
{
	if (ft_strcmp(cmd, "echo"))
	{
		if (!print_echo_args(args))
			printf("\n");
	}
	else if (ft_strcmp(cmd, "export"))
	{
		ft_export(env_list, args);
	}
	else if (ft_strcmp(cmd, "unset"))
	{
		ft_unset(env_list, args);
	}
	else if (ft_strcmp(cmd, "cd"))
	{
		ft_chdir(env_list, args);
	}
	else if (ft_strcmp(cmd, "pwd"))
	{
		ft_pwd(env_list);
	}
	// else if (ft_strcmp(cmd, "exit"))
	// 	ft_exit(env_list, args);
	return (0);
}
