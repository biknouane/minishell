/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look_ahead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:02:10 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/09 12:14:35 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function skips the spaces and 
/// see what is the next token
/// @return 1 if it finds it or 0 if not
int	look_ahead(t_param_holder *params, char *tokens)
{
	while (params->input < params->end_str && \
		ft_strchr("\t\r\n\v ", *(params->input)))
		(params->input)++;
	return (*(params->input) && ft_strchr(tokens, *(params->input)));
}
