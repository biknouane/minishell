/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 18:47:20 by mbiknoua          #+#    #+#             */
/*   Updated: 2022/11/23 18:48:02 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	my_strlen(char *s)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s && s[i])
	{
		i++;
		counter++;
	}
	return (counter);
}

char	*save_to_str_holder(char *str_holder)
{
	char	*new_str;
	int		counter;
	int		j;

	counter = 0;
	j = 0;
	while (str_holder[counter] && str_holder[counter] != '\n')
		counter++;
	if (str_holder[counter] == '\0' \
			|| (str_holder[counter] == '\n' && str_holder[counter + 1] == '\0'))
	{
		free(str_holder);
		return (NULL);
	}
	counter++;
	new_str = (char *)malloc((my_strlen(str_holder) - counter) + 1);
	if (!new_str)
		return (NULL);
	while (str_holder[counter])
		new_str[j++] = str_holder[counter++];
	new_str[j] = '\0';
	free(str_holder);
	return (new_str);
}

int	my_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (unsigned char) c)
			return (1);
		i++;
	}
	return (0);
}
