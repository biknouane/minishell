/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_nv_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:14:53 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/09 02:21:40 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

	ptr = str;
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
