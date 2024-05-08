/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:30:03 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 04:30:37 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function checks if the str is -n or -nnnn....
static int	is_new_line(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (i < ft_strlen(str))
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// this function prints the args and ignors the first -n 
// and then prints new line if there is -n at the beginning
int	print_echo_args(char **args)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (args[i] && is_new_line(args[i]))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	return (flag);
}
