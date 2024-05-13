/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:28:41 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 15:05:04 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	check_is_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '\0')
		return (-1);
	if (str[i] != '+' && str[i] != '-')
		++i;
	while (str[i])
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
			return (0);
		i++;
	}
	return (1);
}

//this function handles the exit builtin
int	ft_exit(char **args, int *exit_status)
{
	if (args[0] != '\0' && args[1] != '\0')
	{
		printf("minishell: exit: too many arguments\n");
		*exit_status = 1;
		return (-1);
	}
	else if (args[0] && check_is_number(args[0]) == 0)
	{
		printf("minishell: exit: %s: numeric argument required\n", args[0]);
		exit (-1);
	}
	else if (args[0] != '\0' && args[1] == '\0')
		exit(ft_atoi(args[0]));
	exit(0);
}
