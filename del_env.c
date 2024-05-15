/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:27:53 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/14 22:48:49 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	is_there_env(t_list **env_list, char *str)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	del_env(t_list **env, char *str)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	if (!is_there_env(env, str))
		return ;
	if (tmp != NULL && ft_strcmp(tmp->key, str))
	{
		*env = tmp->next;
		free_env(tmp);
		return ;
	}
	while (tmp != NULL && !ft_strcmp(tmp->key, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free_env(tmp);
}
