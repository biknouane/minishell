/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:34:49 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 04:35:06 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function handles the chdir builtin
int	ft_chdir(t_list **env_list, char **str)
{
	t_list	*old;
	t_list	*now;
	char	*tmp;

	if (!str)
	{
		now = find_env(env_list, "HOME");
		tmp = ft_strdup(now->value);
	}
	else
		tmp = ft_strdup(str[0]);
	if (chdir(tmp))
	{
		printf("Minishell: %s", str);
		perror("");
		return ;
	}
	now = find_env(env_list, "PWD");
	old = find_env(env_list, "OLDPWD");
	free(old->value);
	old->value = now->value;
	now->value = tmp;
}
