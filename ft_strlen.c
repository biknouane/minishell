/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:19:24 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/12 14:43:01 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s && *s)
	{
		s++;
		i++;
	}
	return (i);
}