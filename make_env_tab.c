/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:12:23 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 00:21:00 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	count_node(t_list **env)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = *env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

static char	*make_var(t_list *node)
{
	char	*str;
	char	*tmp_one;

	tmp_one = ft_strjoin(node->key, "=");
	str = ft_strjoin(tmp_one, node->value);
	free(tmp_one);
	return (str);
}

char	**make_env_tab(t_list **env)
{
	t_list	*tmp;
	char	**tab;
	int		nodes_count;
	int		i;

	i = 0;
	tmp = *env;
	nodes_count = count_node(env);
	tab = (char **)ft_calloc(nodes_count + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < nodes_count)
	{
		tab[i] = make_var(tmp);
		tmp = tmp->next;
		i++;
	}
	return (tab);
}
