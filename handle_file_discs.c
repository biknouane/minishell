/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_discs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 18:17:44 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 18:18:13 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	handle_redirections(t_param_holder *params)
{
	int	i;

	i = 0;
	while (i < params->fd_index)
	{
		dup2(params->files_table[i], params->fd_table[i]);
		i++;
	}
}

void	close_open_fds(t_param_holder *params)
{
	int	i;

	i = 0;
	while (i < params->fd_index)
	{
		close(params->files_table[i]);
		i++;
	}
}
