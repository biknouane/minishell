/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:09:00 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 14:09:00 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	my_lstdelone(t_file_infos **lst, t_file_infos *returned_node)
{
	t_file_infos	*temp_poin_on_node;

	temp_poin_on_node = *lst;
	while (temp_poin_on_node)
	{
		if (temp_poin_on_node->next == returned_node)
		{
			temp_poin_on_node->next = returned_node->next;
			break ;
		}
		else if (temp_poin_on_node == returned_node)
		{
			*lst = temp_poin_on_node->next;
			temp_poin_on_node = returned_node->next;
			break ;
		}
		temp_poin_on_node = temp_poin_on_node->next;
	}
	free (returned_node);
	returned_node = NULL;
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

t_file_infos	*my_lstnew_add_back(t_file_infos **lst, int fd)
{
	t_file_infos	*node;
	t_file_infos	*temp_pointer;

	node = (t_file_infos *)malloc(sizeof(t_file_infos));
	if (!node)
		exit(1);
	node->fd = fd;
	node->str_holder = NULL;
	node->next = NULL;
	temp_pointer = *lst;
	if (*lst)
	{
		while (temp_pointer->next)
			temp_pointer = temp_pointer->next;
		temp_pointer->next = node;
	}
	else
		(*lst) = node;
	return (node);
}

char	*get_next_line(int fd)
{
	static t_file_infos	*list_head;
	t_file_infos		*temp_pointer_on_node;
	char				*str_to_return;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	str_to_return = NULL;
	temp_pointer_on_node = list_head;
	while (temp_pointer_on_node)
	{
		if (temp_pointer_on_node->fd == fd)
			break ;
		temp_pointer_on_node = temp_pointer_on_node->next;
	}
	if (!temp_pointer_on_node)
		temp_pointer_on_node = my_lstnew_add_back(&list_head, fd);
	temp_pointer_on_node->str_holder = \
				read_from_the_file(fd, temp_pointer_on_node->str_holder);
	if (!temp_pointer_on_node->str_holder)
		return (my_lstdelone(&list_head, temp_pointer_on_node), NULL);
	str_to_return = return_the_line(temp_pointer_on_node->str_holder);
	temp_pointer_on_node->str_holder = \
				save_to_str_holder(temp_pointer_on_node->str_holder);
	return (str_to_return);
}
