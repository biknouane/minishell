/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   see_ahead.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 13:44:17 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 13:44:37 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	see_ahead(char *str, char *tokens)
{
	while (str < (str + ft_strlen(str)) && ft_strchr("\t\r\n\v ", *str))
		str++;
	return (*str && ft_strchr(tokens, *str));
}
