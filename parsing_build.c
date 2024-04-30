/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:36:38 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/30 01:52:45 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// parse_pipe ===> parse_redirs ===> parse_exec
int	main(void)
{
	char	*str;
	char	*end_str;
	char	*ret;
	t_token	tok;
	t_state	state;

	str = "\"e\"'c''h'\"o\"'b' \"hello 'nor' bik\" > tmp | ls -la";
	end_str = str + ft_strlen(str);
	state = NORMAL;
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, NULL, &state);
	ret = NULL;
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	tok = get_token(&str, end_str, &ret, &state);
	printf("%s\n", ret);
	printf("===========================\n");
	// while ((tok = get_token(&str, end_str, &ret, &state)) != 0)
	// {
	// 	// printf("%d\n", tok);
	// 	printf("%s\n", ret);
	// }
	return (0);
}
