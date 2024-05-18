/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_string_quotes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:17:48 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 01:38:14 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is for handling the striping for single quotes
static void	handle_striping_single_quote(char *str, t_strip_quotes *tmp)
{
	if ((*tmp).doub_q % 2 != 0)
		str[(*tmp).j++] = str[(*tmp).i];
	else
		(*tmp).sin_q++;
}

// this function is for handling the striping for double quotes
static void	handle_striping_double_quote(char *str, t_strip_quotes *tmp)
{
	if ((*tmp).sin_q % 2 != 0)
		str[(*tmp).j++] = str[(*tmp).i];
	else
		(*tmp).doub_q++;
}

//this is for striping the quotes from the string
//and this need to be passed allocated
int	strip_string_quotes(char *str, int *single_q_n, int *double_q_n)
{
	t_strip_quotes	tmp;

	tmp.i = 0;
	tmp.j = 0;
	tmp.sin_q = 0;
	tmp.doub_q = 0;
	while (str[tmp.i])
	{
		if (str[tmp.i] == '\'')
			handle_striping_single_quote(str, &tmp);
		else if (str[tmp.i] == '"')
			handle_striping_double_quote(str, &tmp);
		else
			str[tmp.j++] = str[tmp.i];
		tmp.i++;
	}
	str[tmp.j] = '\0';
	if (single_q_n)
		*single_q_n = tmp.sin_q;
	if (double_q_n)
		*double_q_n = tmp.doub_q;
	return (tmp.sin_q - tmp.doub_q);
}
