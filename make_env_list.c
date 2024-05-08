/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:35:35 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 05:35:49 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	make_env_list(t_list **env_list, char **env)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_list));
		if (!tmp)
			return ;
		split_env(tmp, env[i]);
		ft_lstadd_back(env_list, tmp);
		i++;
	}
}
