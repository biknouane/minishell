/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_ret_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:22:47 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 20:23:23 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is to set the return token to a redirection or word
static void	handle_redirs(t_token *ret, t_param_holder *params)
{
	if (*(params->input) == '>')
	{
		*ret = RE_OUT;
		(params->input)++;
		if (*(params->input) == '>')
		{
			*ret = APEND;
			(params->input)++;
		}
	}
	else if (*(params->input) == '<')
	{
		*ret = RE_IN;
		(params->input)++;
		if (*(params->input) == '<')
		{
			*ret = H_DOK;
			(params->input)++;
		}
	}
	else
	{
		*ret = WORD;
		parse_string(params);
	}
}

// this function is for setting the return token to a pipe or null
void	set_ret_token(t_token *ret, t_param_holder *params)
{
	if (*(params->input) == 0)
		*ret = *(params->input);
	else if (*(params->input) == '|')
	{
		*ret = PIP;
		(params->input)++;
	}
	else
		handle_redirs(ret, params);
}
