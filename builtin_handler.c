/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:36:20 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 04:36:35 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this is the alternative of execve of builtings
int	handle_builtin(char	*cmd, char **args, t_list **env_list)
{
	char	*tmp;

	if (ft_strcmp(cmd, "echo"))
	{
		if (!print_echo_args(*args[1]))
			printf("\n");
	}
	else if (ft_strcmp(cmd, "export"))
	{
		ft_export(env_list, *args[1]);
	}
}
