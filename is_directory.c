/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_directory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:57:18 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 17:58:41 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	is_directory(char *path)
{
	struct stat	info;

	if (stat(path, &info) != 0)
		return (0);
	return (S_ISDIR(info.st_mode));
}
