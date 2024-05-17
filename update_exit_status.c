/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:51:33 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 17:51:53 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	update_exit_status(int *exit_status)
{
	unsigned char	*sts;

	sts = (unsigned char *)exit_status;
	if (sts[0])
		*exit_status = sts[0] + 128;
	else
		*exit_status = sts[1];
}
