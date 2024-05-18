/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:52:09 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 21:42:52 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function is the entry of the parsing functionality
/// @param str the line enterd by the user
/// @param env_list the environment variables in form of a linked list
/// @param exit_status a pointer to the exit satatus of a child process
/// @return tree of commands to execute
t_command	*parse_cmd(t_param_holder *params)
{
	t_command	*cmd;

	params->end_str = params->input + ft_strlen(params->input);
	cmd = parse_pipe(params);
	return (cmd);
}
