/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_is_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:38:23 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 05:38:38 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	ft_str_is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (!ft_is_space(line[i++]))
			return (0);
	return (1);
}
