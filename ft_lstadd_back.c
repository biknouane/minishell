/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:14:55 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 05:15:12 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_pointer;

	if (!lst || !new)
		return ;
	temp_pointer = *lst;
	if (*lst)
	{
		while (temp_pointer->next)
			temp_pointer = temp_pointer->next;
		temp_pointer->next = new;
	}
	else
		(*lst) = new;
}
