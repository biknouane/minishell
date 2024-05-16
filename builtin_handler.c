/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:36:20 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/16 13:04:43 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this is the alternative of execve of builtings
int	handle_builtin(char	*cmd, char **args, t_list **env_list, int *exit_status)
{
	if (ft_strcmp(cmd, "echo"))
	{
		if (!print_echo_args(args))
			printf("\n");
	}
	else if (ft_strcmp(cmd, "export"))
		return (ft_export(env_list, args));
	else if (ft_strcmp(cmd, "unset"))
		return (ft_unset(env_list, args));
	else if (ft_strcmp(cmd, "cd"))
		return (ft_chdir(env_list, args));
	else if (ft_strcmp(cmd, "pwd"))
		return (ft_pwd());
	else if (ft_strcmp(cmd, "exit"))
		return (ft_exit(&args[1], exit_status));
	else if (ft_strcmp(cmd, "env"))
		return (ft_env(env_list));
	return (0);
}
