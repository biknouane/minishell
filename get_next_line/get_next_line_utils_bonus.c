/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:09:14 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 14:09:19 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	if (!str_holder)
		return (NULL);
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
		exit(1);
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

void	process_final_str(char *s1, char *s2, char *temp_pointer)
{
	int	i;

	i = 0;
	while (s1 && s1[i])
	{
		*temp_pointer = s1[i];
		temp_pointer++;
		i++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		*temp_pointer = s2[i];
		temp_pointer++;
		s2++;
	}
	*temp_pointer = '\0';
}

char	*my_strjoin(char *str_holder, char *s2)
{
	char	*final_str;
	int		s_one_len;
	int		s_two_len;

	if (!str_holder && !s2)
		return (NULL);
	s_one_len = my_strlen(str_holder);
	s_two_len = my_strlen(s2);
	final_str = (char *)malloc(s_two_len + s_one_len + 1);
	if (!final_str)
		exit(1);
	process_final_str(str_holder, s2, final_str);
	if (str_holder)
		free(str_holder);
	return (final_str);
}
