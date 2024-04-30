/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 14:57:46 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/30 00:35:04 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include <string.h>

typedef enum s_state
{
	NORMAL,
	IN_SINGLE_QUOTE,
	IN_DOUBLE_QUOTE
}			t_state;

void	parse_string(char **str, t_state *state)
{
	char	*tmp;
	int		i;

	tmp = *str;
	i = 0;
	while (tmp[i])
	{
		if (*state == NORMAL)
		{
			if (ft_strchr("<|> ", tmp[i++]))
			{
				*str = tmp;
				return ;
			}
			else if (tmp[i++] == '\'')
				*state = IN_SINGLE_QUOTE;
			else if (tmp[i++] == '"')
				*state = IN_DOUBLE_QUOTE;
		}
		else if (*state == IN_SINGLE_QUOTE)
		{
			if (tmp[i++] == '\'')
				*state = NORMAL;
		}
		else if (*state == IN_DOUBLE_QUOTE)
		{
			if (tmp[i++] == '"')
				*state = NORMAL;
		}
	}
}
typedef enum s_token
{
	PIP = 124,
	RE_IN = 60,
	RE_OUT = 62,
	H_DOK = 45,
	APEND = 43,
	WORD = 97
}			t_token;

int	main(void)
{
	t_token	tok;

	tok = PIP;
	if (tok == '|')
		printf("we can compare them\n");
	return (0);
}
