/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:18:50 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 05:19:02 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strdup(const char *s1)
{
	size_t	str_len;
	char	*new_str;

	str_len = ft_strlen(s1);
	new_str = malloc(str_len + 1);
	if (!new_str)
		return (NULL);
	while (*s1)
	{
		*new_str = *s1;
		s1++;
		new_str++;
	}
	*new_str = '\0';
	return (new_str - str_len);
}
