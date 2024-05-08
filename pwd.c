/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:35:25 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 04:35:51 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function handles the pwd builtin
int	ft_pwd(t_list **env_list)
{
	t_list	*tmp;

	tmp = find_env(env_list, "PWD");
	printf("%s\n", tmp->value);
}
