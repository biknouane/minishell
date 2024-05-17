/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:34:49 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 13:01:04 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function handles the chdir builtin
int	ft_chdir(t_list **env_list, char **str)
{
	t_list	*old;
	t_list	*new;
	char	*tmp;
	char	path[300];

	if (!str[1])
	{
		new = find_env(env_list, "HOME");
		if (new == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set", 2);
			return (1);
		}
		tmp = ft_strdup(new->value);
	}
	else
		tmp = ft_strdup(str[1]);
	if (chdir(tmp))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(tmp);
		return (1);
	}
	new = find_env(env_list, "PWD");
	old = find_env(env_list, "OLDPWD");
	if (old)
	{
		free(old->value);
		if (new)
			old->value = ft_strdup(new->value);
		else
			old->value = NULL;
	}
	if (new)
	{
		free(new->value);
		new->value = ft_strdup(getcwd(path, 299));
	}
	return (free(tmp), 0);
}
