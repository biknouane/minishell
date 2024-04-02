/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 07:56:10 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/01 02:59:29 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	ft_echo(char *str, bool flag)
{
	printf("%s", str);
	if (flag)
		printf("\n");
}

void	ft_export(t_list **env, char *str)
{
	t_list	*var;

	var = ft_calloc(1, sizeof(t_list));
	split_env(var, str);
	ft_lstadd_back(env, var);
}

void	ft_unset(t_list **env, char *str)
{
	del_env(env, str);
}

void	ft_env(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_exit(char *str)
{
	int	num;

	num = ft_atoi(str);
	exit(num);
}

void	ft_chdir(t_list **env_list, char *str)
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
		tmp = ft_strdup(str);
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

void	ft_pwd(t_list **env_list)
{
	t_list	*tmp;

	tmp = find_env(env_list, "PWD");
	printf("%s\n", tmp->value);
}
