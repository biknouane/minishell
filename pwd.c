/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:35:25 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/14 00:07:20 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function handles the pwd builtin
int	ft_pwd(void)
{
	char	tmp[300];

	printf("%s\n", getcwd(tmp, 299));
	return (0);
}
