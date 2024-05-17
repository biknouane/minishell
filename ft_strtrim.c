/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:33:43 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 20:33:58 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start_of_str;
	char	*end_of_str;
	int		len;

	if (!*set)
		return (ft_strdup(s1));
	if (!*s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	start_of_str = (char *)s1;
	end_of_str = (char *)s1 + ft_strlen(s1);
	while (*start_of_str && ft_strchr(set, (int) *start_of_str))
		start_of_str++;
	while (len && ft_strrchr(set, (int) *end_of_str))
	{
		end_of_str--;
		len--;
	}
	if (start_of_str > end_of_str)
		return (ft_strdup(""));
	return (ft_substr(s1, (start_of_str - s1) \
	, (int)(end_of_str - start_of_str) + 1));
}
