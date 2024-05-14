/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:26:47 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 14:52:06 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

t_list	*find_env(t_list **env_list, char *str)
{
	t_list	*env_var;
	int		i;

	env_var = *env_list;
	i = 0;
	while (env_var)
	{
		if (ft_strcmp(env_var->key, str))
			return (env_var);
		env_var = env_var->next;
	}
	return (NULL);
}