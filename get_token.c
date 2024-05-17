/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:29:56 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 20:23:19 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is to initialise the state variable
static void	initialise_state(t_param_holder *params, char tmp)
{
	if (tmp == '"')
		params->state = IN_DOUBLE_QUOTE;
	else if (tmp == '\'')
		params->state = IN_SINGL_QUOTE;
	else
		params->state = NORMAL;
}

// this function is tho escape the leading space
static void	escape_leading_space(t_param_holder *params)
{
	if (params->state == NORMAL)
	{
		while (params->input < params->end_str && \
				ft_strchr("\t\r\n\v ", *(params->input)))
			(params->input)++;
	}
}

static void	escape_tailing_spaces(t_param_holder *params)
{
	while ((params->input) < params->end_str && \
		ft_strchr("\t\r\n\v ", *(params->input)))
		(params->input)++;
}

// this function is the tokenizer and get us the next token
t_token	get_token(t_param_holder *params, char **str_ret)
{
	char	*start_token;
	char	*end_token;
	char	*tmp;
	t_token	ret;

	ret = 0;
	if (params->input == params->end_str)
		return (ret);
	initialise_state(params, *(params->input));
	escape_leading_space(params);
	if (str_ret)
		start_token = params->input;
	ret = *(params->input);
	set_ret_token(&ret, params);
	if (str_ret)
	{
		end_token = params->input;
		tmp = ft_substr(start_token, 0, end_token - start_token);
		free(*str_ret);
		*str_ret = NULL;
		*str_ret = tmp;
	}
	escape_tailing_spaces(params);
	return (ret);
}
