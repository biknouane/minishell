/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:32:16 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 04:33:03 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

// this function is to check if the str contains 
// any other chars not '_' of nums or alphanumerics
static int	is_valid_var(char *str)
{
	int	i;

	i = 1;
	if (str[0] == '=')
		return (0);
	while (i < ft_strlen(str) && str[i] != '=')
	{
		if (str[i] != '_' && !(str[i] <= '9' && str[i] >= '0') && \
			!(str[i] <= 'Z' && str[i] >= 'A') && \
			!(str[i] <= 'z' && str[i] >= 'a'))
			return (0);
		i++;
	}
	return (1);
}

// this function handles the error if the args is not valid
static int	handle_unset_error(char *str)
{
	printf("minishell: unset: \'%s\': not a valid identifier\n", \
						str);
	return (-1);
}

// this function handles unset builtin
int	ft_unset(t_list **env, char **str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	if (str)
	{
		while (str[i])
		{
			if (is_valid_var(str[i]))
				del_env(env, str);
			else
				ret = handle_unset_error(str[i]);
			i++;
		}
	}
	return (ret);
}
