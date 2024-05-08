/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:28:41 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 04:29:18 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_is_number(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '\0')
		return (-1);
	if (str[0] != '+' && str[0] != '-')
		return (-1);
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (-1);
		i++;
	}
	return (0);
}

//this function handles the exit builtin
int	ft_exit(char **str, int exit_status)
{
	if (check_is_number(str[0]))
	{
		printf("minishell: exit: %s: numeric argument required\n", str[0]);
		exit (-1);
	}
	else if (str[0] != '\0' && str[1] != '\0')
	{
		printf("minishell: exit: too many arguments\n");
		exit_status = 1;
	}
	else if (str[0] != '\0' && str[1] == '\0')
		exit(ft_atoi(str[0]));
	else
		exit(0);
}
