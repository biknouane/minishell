/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_hadle_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:07:04 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 22:07:12 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	handle_quotes_and_error(t_param_holder *params, char **arg)
{
	if (strip_string_quotes(*arg, NULL, NULL) % 2)
	{
		print_error("syntax error you need to close the quotes");
		free(*arg);
		*arg = NULL;
		params->exit_status = 258;
		params->is_error = 1;
		return (1);
	}
	return (0);
}
