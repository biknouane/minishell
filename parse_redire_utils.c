/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redire_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:27:25 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 22:29:22 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_resources(char *file, char *eof)
{
	free(file);
	free(eof);
}

int	get_file_flags(t_token token)
{
	if (token == RE_IN)
		return (O_RDONLY);
	else if (token == RE_OUT)
		return (O_RDWR | O_CREAT | O_TRUNC);
	else if (token == APEND)
		return (O_RDWR | O_CREAT | O_APPEND);
	return (0);
}
