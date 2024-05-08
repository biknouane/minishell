/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:36:38 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 13:18:04 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// int main() {
//     char str[1000];
// 	int error;
//     printf("Enter a string: ");
//     fgets(str, sizeof(str), stdin);

//      error = strip_string_quotes(str);

//     printf("String without quotes: %s\n", str);
// 	printf("is there an error: %d\n", error);

//     return 0;
// }

// int	main(void)
// {
// 	char	*str;
// 	char	*end_str;
// 	char	*ret;
// 	t_token	tok;
// 	t_state	state;

// 	str = "\"e\"'c''h'\"o\" \"hello 'nor' bik\" > tmp | ls -la";
// 	end_str = str + ft_strlen(str);
// 	state = NORMAL;
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	// ret = NULL;
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	tok = get_token(&str, end_str, &ret, &state);
// 	printf("%s\n", ret);
// 	printf("===========================\n");
// 	// while ((tok = get_token(&str, end_str, &ret, &state)) != 0)
// 	// {
// 	// 	// printf("%d\n", tok);
// 	// 	printf("%s\n", ret);
// 	// }
// 	return (0);
// }
