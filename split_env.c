/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:34:42 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 15:36:03 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	split_env(t_list *env_list, char *str)
{
	char	*dilimiter;
	int		key_lenght;
	int		value_lenght;

	dilimiter = ft_strchr(str, '=');
	if (!dilimiter)
	{
		key_lenght = ft_strlen(str);
		value_lenght = 0;
		env_list->print_with_env = 0;
	}
	else
	{
		key_lenght = dilimiter - str;
		value_lenght = ft_strlen(dilimiter +1);
		env_list->value = ft_calloc(value_lenght + 1, sizeof(char));
		ft_strcpy(env_list->value, dilimiter + 1);
		env_list->print_with_env = 1;
	}
	env_list->key = ft_calloc(key_lenght + 1, sizeof(char));
	ft_strncpy(env_list->key, str, key_lenght);
}
