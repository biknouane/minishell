/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_her_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:48:59 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/09 02:32:13 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static void	find_dollar(char **str)
{
	char	*ptr;

	ptr = *str;
	while (*ptr != '\0' && *ptr != '$')
		ptr++;
	*str = ptr;
}

static void	find_here_dilem(char **tmp)
{
	char	*end;

	end = *tmp;
	while (*end != '\n' && *end != '\'' && *end != '"' && \
				*end != ' ' && *end != '\0')
		end++;
	*tmp = end;
}

static void	replace_var(t_list *node, char **tmp, char *end, char hold)
{
	if (node)
		*tmp = ft_strjoin(*tmp, node->value);
	*end = hold;
	*tmp = ft_strjoin(*tmp, end);
}

/// @brief this function handles the expand inside the her_doc body
/// @param str the line that inputed in the here doc
/// @param env_list environment variables for expansion
/// @return the original string that inputed or 
///         expanded one if there is an expansion
char	*expand_her_doc(char *str, t_list **env_list)
{
	char	*ptr;
	char	*end;
	char	*tmp;
	t_list	*node;
	char	hold;

	ptr = str;
	find_dollar(&ptr);
	if (*ptr != '\0')
	{
		end = ptr + 1;
		if (end && *end != '\n' && *end != '\'' && *end != '"' && \
					*end != ' ' && *end != '\0')
		{
			*ptr = '\0';
			tmp = ft_strjoin(tmp, str);
			printf("this is the value of the env: \n");
			find_here_dilem(&end);
			hold = *end;
			*end = '\0';
			node = find_env(env_list, ptr);
			replace_var(node, &tmp, end, hold);
		}
		else
			tmp = ft_strdup(str);
	}
	else
		tmp = ft_strdup(str);
	if (str)
		free(str);
	return (tmp);
}
