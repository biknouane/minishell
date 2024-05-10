/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:29:56 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/11 00:13:56 by mbiknoua         ###   ########.fr       */
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
static void	set_ret_token(t_token *ret, t_param_holder *params)
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

// this function is the tokenizer and get us the next token
t_token	get_token(t_param_holder *params, char **str_ret)
{
	char	*start_token;
	char	*end_token;
	char	*tmp;
	t_token	ret;

	ret = 0;
	if (params->input == params->end_str)
	{
		printf(" we ar at the end of the input\n");
		return (ret);
	}
	initialise_state(params, *(params->input));
	escape_leading_space(params);
	if (str_ret)
		start_token = params->input;
	ret = *(params->input);
	set_ret_token(&ret, params);
	if (str_ret)
	{
		printf("i ma at returning in the get_token\n");
		end_token = params->input;
		tmp = ft_substr(start_token, 0, end_token - start_token);
		printf("++++++%s\n", tmp);
		free(*str_ret);
		*str_ret = NULL;
		*str_ret = tmp;
	}
	while ((params->input) < params->end_str && \
		ft_strchr("\t\r\n\v ", *(params->input)))
		(params->input)++;
	printf("i am about to return aout of get_token\n");
	return (ret);
}
