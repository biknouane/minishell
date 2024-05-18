/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:16:32 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 14:09:49 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*my_strjoin(char *s1, char *s2)
{
	char	*final_str;
	int		s_one_len;
	int		s_two_len;

	if (!s1 && !s2)
		return (NULL);
	s_one_len = my_strlen(s1);
	s_two_len = my_strlen(s2);
	final_str = (char *)malloc(s_two_len + s_one_len + 1);
	if (!final_str)
		exit(1);
	process_final_str(s1, s2, final_str);
	free(s1);
	return (final_str);
}

char	*return_the_line(char *str_holder)
{
	char	*str_to_return;
	int		counter;
	int		i;

	counter = 0;
	if (!str_holder)
		return (NULL);
	while (str_holder[counter] && str_holder[counter] != '\n')
		counter++;
	if (str_holder[counter] && str_holder[counter] == '\n')
		counter++;
	str_to_return = (char *)malloc(counter + 1);
	if (!str_to_return)
		exit(1);
	i = 0;
	while (str_holder[i] && counter)
	{
		str_to_return[i] = str_holder[i];
		i++;
		counter--;
	}
	str_to_return[i] = '\0';
	return (str_to_return);
}

char	*read_from_the_file(int fd, char *str_holder)
{
	int		counter;
	char	*buffer_holder;

	buffer_holder = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer_holder)
		exit(1);
	while (1)
	{
		counter = read(fd, buffer_holder, BUFFER_SIZE);
		if (counter < 0)
		{
			free(str_holder);
			str_holder = NULL;
			free(buffer_holder);
			return (NULL);
		}
		else if (counter == 0)
			break ;
		buffer_holder[counter] = '\0';
		str_holder = my_strjoin(str_holder, buffer_holder);
		if (my_strchr(buffer_holder, '\n'))
			break ;
	}
	free(buffer_holder);
	return (str_holder);
}

char	*get_next_line(int fd)
{
	static char	*str_holder;
	char		*str_to_return;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	str_to_return = NULL;
	str_holder = read_from_the_file(fd, str_holder);
	if (!str_holder)
		return (NULL);
	str_to_return = return_the_line(str_holder);
	str_holder = save_to_str_holder(str_holder);
	return (str_to_return);
}
