/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:29:56 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 10:42:11 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is to initialise the state variable
static void	initialise_state(t_state *state, char tmp)
{
	if (tmp == '"')
		*state = IN_DOUBLE_QUOTE;
	else if (tmp == '\'')
		*state = IN_SINGL_QUOTE;
	else
		*state = NORMAL;
}

// this function is to set the return token to a redirection or word
static void	handle_redirs(t_token *ret, char **tmp, t_state *state)
{
	if (*tmp == '>')
	{
		ret = RE_OUT;
		tmp++;
		if (*tmp == '>')
		{
			ret = APEND;
			tmp++;
		}
	}
	else if (*tmp == '<')
	{
		ret = RE_IN;
		tmp++;
		if (*tmp == '<')
		{
			ret = H_DOK;
			tmp++;
		}
	}
	else
	{
		ret = WORD;
		parse_string(&tmp, state);
	}
}

// this function is for setting the return token to a pipe or null
static void	set_ret_token(t_token *ret, char **tmp, t_state *state)
{
	if (*tmp == 0)
		ret = *tmp;
	else if (*tmp == '|')
	{
		ret = PIP;
		tmp++;
	}
	else
		handle_redirs(ret, tmp, state);
}

// this function is tho escape the leading space
static void	escape_leading_space(t_state *state, char *end_str, char **tmp)
{
	if (*state == NORMAL)
	{
		while (*tmp < end_str && ft_strchr("\t\r\n\v ", **tmp))
			(*tmp)++;
	}
}

// this function is the tokenizer and get us the next token
t_token	get_token(char	**str, char *end_str, char **str_ret, t_state *state)
{
	char	*tmp;
	char	*next;
	char	*start_token;
	char	*end_token;
	t_token	ret;

	tmp = *str;
	initialise_state(state, *tmp);
	escape_leading_space(state, end_str, &tmp);
	if (str_ret)
		start_token = tmp;
	ret = *tmp;
	set_ret_token(&ret, &tmp, state);
	if (str_ret)
	{
		end_token = tmp;
		*str_ret = ft_substr(start_token, 0, end_token - start_token);
	}
	while (tmp < end_str && ft_strchr("\t\r\n\v ", *tmp))
		tmp++;
	*str = tmp;
	return (ret);
}
