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

// static void	find_dollar(char **str)
// {
// 	char	*ptr;

// 	ptr = *str;
// 	while (*ptr != '\0' && *ptr != '$')
// 		ptr++;
// 	*str = ptr;
// }

// static void	find_here_dilem(char **tmp)
// {
// 	char	*end;

// 	end = *tmp;
// 	while (*end != '\n' && *end != '\'' && *end != '"' && \
// 				*end != ' ' && *end != '\0')
// 		end++;
// 	*tmp = end;
// }

// static void	replace_var(t_list *node, char **tmp, char *end, char hold)
// {
// 	if (node)
// 		*tmp = ft_strjoin(*tmp, node->value);
// 	*end = hold;
// 	*tmp = ft_strjoin(*tmp, end);
// }

/// @brief this function handles the expand inside the her_doc body
/// @param str the line that inputed in the here doc
/// @param env_list environment variables for expansion
/// @return the original string that inputed or 
///         expanded one if there is an expansion

int get_key_length(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n' || str[i] == '\'' || str[i] == '"' || \
			str[i] == ' ' || str[i] == '\0' || str[i] == '$' || str[i] == '?')
			return (i);
		++i;
	}
	return (i);
}

void	expand_her_doc(char *str, t_list **env_list, int fd)
{
	t_list	*node;
	char	*key;
	int		len;
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			++i;
			len = get_key_length(&str[i]);
			key = ft_substr(&str[i], 0, len);
			node = find_env(env_list, key);
			if (node)
				ft_putstr_fd(node->value, fd);
			if (len == 0)
				ft_putchar_fd('$', fd);
			i += len;
			free(key);
		}
		else
			ft_putchar_fd(str[i++], fd);
	}
	ft_putchar_fd('\n', fd);
}
