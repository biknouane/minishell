/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finite_state_m.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:00:42 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 10:42:36 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for handling the quote state
static void	handle_quote_state(t_state *state, char tmp)
{
	if (*state == IN_SINGL_QUOTE)
	{
		if (tmp == '\'')
			*state = NORMAL;
	}
	else if (*state == IN_DOUBLE_QUOTE)
	{
		if (tmp == '"')
			*state = NORMAL;
	}
}

// this function is for changing the state of the tokenizer
void	parse_string(char **str, t_state *state)
{
	char	*tmp;

	tmp = *str;
	tmp++;
	while (*tmp)
	{
		if (*state == NORMAL)
		{
			if (ft_strchr("<|> ", *tmp))
			{
				*str = tmp;
				return ;
			}
			else if (*tmp == '\'')
				*state = IN_SINGL_QUOTE;
			else if (*tmp == '"')
				*state = IN_DOUBLE_QUOTE;
		}
		else
			handle_quote_state(state, *tmp);
		tmp++;
	}
	*str = tmp;
}
