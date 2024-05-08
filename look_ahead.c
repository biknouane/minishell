/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_ahead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:02:10 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 10:03:44 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for looking what is the next token
int	look_ahead(char **str, char *end_str, char *tokens)
{
	char	*tmp;
	char	*white_space;

	tmp = *str;
	white_space = "\t\r\n\v ";
	while (tmp < end_str && ft_strchr(white_space, *tmp))
		tmp++;
	*str = tmp;
	return (*tmp && ft_strchr(tokens, *tmp));
}
