/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_holder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:10:56 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 00:21:18 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// parce_cmd ===> parse_pipe ===> parse_redirs ===> parse_exec
// this function is to handle the expand of env var in her_doc
char	*expand_herdoc(char *line, char **env_list)
{
	char	*new_herdoc;

	new_herdoc = expand_her_doc(line, env_list);
	return (new_herdoc);
}
