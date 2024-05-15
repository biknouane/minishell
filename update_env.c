/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 13:03:59 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/15 19:08:16 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/// @brief this function updates the environment variables list
/// @param env the environment variables lis
/// @param str the var that will change with it's value
void	update_env(t_list **env, char *str)
{
	char	*key;
	char	*value;
	char	*dilimiter;
	int		str_lenght;
	t_list	*tmp;

	key = NULL;
	value = NULL;
	dilimiter = ft_strchr(str, '=');
	printf("am i inside the first if in the ft_export, key= %s\n", dilimiter);
	if (dilimiter)
	{
		str_lenght = dilimiter - str;
		key = ft_calloc(str_lenght + 1, sizeof(char));
		if (!key)
			return ;
		ft_strncpy(key, str, str_lenght);
		tmp = find_env(env, key);
		if (tmp == NULL)
			return (free(key));
		str_lenght = ft_strlen(dilimiter +1);
		value = ft_calloc(str_lenght + 1, sizeof(char));
		if (!value)
			return ;
		ft_strcpy(value, dilimiter + 1);
		free(tmp->value);
		tmp->value = value;
		tmp->print_with_env = 1;
		free(key);
	}
}
