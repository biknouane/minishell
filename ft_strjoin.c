/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:11:04 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 05:11:23 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;
	char	*temp_pointer;
	int		s_one_len;
	int		s_two_len;

	s_one_len = ft_strlen(s1);
	s_two_len = ft_strlen(s2);
	final_str = (char *)malloc(s_two_len + s_one_len + 1);
	if (!final_str)
		return (NULL);
	temp_pointer = final_str;
	while (*s1)
	{
		*temp_pointer = *s1;
		temp_pointer++;
		s1++;
	}
	while (*s2)
	{
		*temp_pointer = *s2;
		temp_pointer++;
		s2++;
	}
	*temp_pointer = '\0';
	return (final_str);
}
