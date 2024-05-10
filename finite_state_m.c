/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finite_state_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:00:42 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 11:02:44 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for handling the quote state
static void	handle_quote_state(t_param_holder *params)
{
	if (params->state == IN_SINGL_QUOTE)
	{
		if (*(params->input) == '\'')
			params->state = NORMAL;
	}
	else if (params->state == IN_DOUBLE_QUOTE)
	{
		if (*(params->input) == '"')
			params->state = NORMAL;
	}
}

// this function is for changing the state of the tokenizer
void	parse_string(t_param_holder *params)
{
	(params->input)++;
	while (*(params->input))
	{
		if (params->state == NORMAL)
		{
			if (ft_strchr("<|> ", *(params->input)))
				return ;
			else if (*(params->input) == '\'')
				params->state = IN_SINGL_QUOTE;
			else if (*(params->input) == '"')
				params->state = IN_DOUBLE_QUOTE;
		}
		else
			handle_quote_state(params);
		(params->input)++;
	}
}
