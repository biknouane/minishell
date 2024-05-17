/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:34:49 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 17:48:37 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"


static int	cd_to_home(char *str, t_list **new, char **tmp, t_list **env_list)
{
	if (!str)
	{
		*new = find_env(env_list, "HOME");
		if (*new == NULL)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		*tmp = ft_strdup((*new)->value);
	}
	else
		*tmp = ft_strdup(str);
	return (0);
}

static void	set_old_pwd(t_list *old, t_list *new, t_list **env_list)
{
	if (old)
	{
		free(old->value);
		if (new)
			old->value = ft_strdup(new->value);
		else
			old->value = NULL;
	}
	else
	{
		old = ft_calloc(1, sizeof(t_list));
		old->key = ft_strdup("OLDPWD");
		if (new)
			old->value = ft_strdup(new->value);
		else
			old->value = NULL;
		ft_lstadd_back(env_list, old);
	}
}

static void	set_new_pwd(t_list *new, t_list **env_list, char *path)
{
	if (new)
	{
		free(new->value);
		new->value = ft_strdup(getcwd(path, 299));
	}
	else
	{
		new = ft_calloc(1, sizeof(t_list));
		new->key = ft_strdup("PWD");
		new->value = ft_strdup(getcwd(path, 299));
		ft_lstadd_back(env_list, new);
	}
}

/// @brief this function handles the chdir builtin
/// @param env_list the environment list
/// @param str the argument to cd in to
/// @return 0 seccess or 1 failure
int	ft_chdir(t_list **env_list, char **str)
{
	t_list	*old;
	t_list	*new;
	char	*tmp;
	char	path[300];

	new = NULL;
	tmp = NULL;
	if (cd_to_home(str[1], &new, &tmp, env_list))
		return (1);
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
	set_old_pwd(old, new, env_list);
	set_new_pwd(new, env_list, path);
	return (free(tmp), 0);
}
