/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 21:36:38 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/02 02:29:10 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// you need to free this str param after calling this function
// and this str param needs to be allocated befor passing it 
// because we modify it inside
char	*expand_nv_var(char *str, t_list **env_list)
{
	char	*ptr;
	char	*end;
	char	*tmp;
	t_list	*node;
	char	hold;

	tmp = NULL;
	while (*ptr != '\0' && *ptr != '$')
		ptr++;
	*ptr = '\0';
	tmp = ft_strjoin(tmp, str);
	ptr++;
	end = ptr;
	while (*end != '\0' && *end != '\'' && *end != '"' && *end != ' ')
		end++;
	hold = *end;
	*end = '\0';
	node = find_env(env_list, ptr);
	if (node)
		tmp = ft_strjoin(tmp, node->value);
	*end = hold;
	tmp = ft_strjoin(tmp, end);
	return (tmp);
}

//this is for striping the quotes from the string
//and this need to be bassed allocated
int	string_quotes(char *str)
{
	int	i;
	int	j;
	int	sin_q;
	int	doub_q;

	i = 0;
	j = 0;
	sin_q = 0;
	doub_q = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (doub_q % 2 != 0)
				str[j++] = str[i];
			else
				sin_q++;
		}
		else if (str[i] == '"')
		{
			if (sin_q % 2 != 0)
				str[j++] = str[i];
			else
				doub_q++;
		}
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (sin_q - doub_q);
}

// int main() {
//     char str[1000];
// 	int error;
//     printf("Enter a string: ");
//     fgets(str, sizeof(str), stdin);

//      error = string_quotes(str);

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
