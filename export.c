/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 04:31:06 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/14 22:50:08 by mbiknoua         ###   ########.fr       */
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

// this is a helper function to print export with no args
static void	handle_print_export(t_list **env)
{
	t_list	*var;

	var = *env;
	while (var)
	{
		printf("declare -x %s", var->key);
		if (var->value)
			printf("=\"%s\"", var->value);
		printf("\n");
		var = var->next;
	}
}

// this function handles printing error of 
// exprot function if the str is not valid
static int	handle_export_error(char *str)
{
	printf("minishell: export: \'%s\': not a valid identifier\n", \
						str);
	return (-1);
}

static int	is_present_in_list(t_list **env, char *str)
{
	t_list	*tmp;
	char	*dilimiter;
	char	*str_key;
	int		key_len;

	dilimiter = str;
	tmp = *env;
	while (dilimiter && *dilimiter != '=' && *dilimiter != '\0')
		dilimiter++;
	key_len = dilimiter - str;
	str_key = ft_calloc(key_len + 1, 1);
	ft_strncpy(str_key, str, key_len);
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str_key))
		{
			free(str_key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(str_key);
	return (0);
}

// this function handles the export builtin and coudld handle multiple args
int	ft_export(t_list **env, char **str)
{
	t_list	*var;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	if (str[i])
	{
		while (str[i])
		{
			if (is_valid_var(str[i]))
			{
				if (!is_present_in_list(env, str[i]))
				{
					var = ft_calloc(1, sizeof(t_list));
					split_env(var, str[i]);
					ft_lstadd_back(env, var);
				}
				else
					update_env(env, str[i]);
			}
			else
				ret = handle_export_error(str[i]);
			i++;
		}
	}
	else
		handle_print_export(env);
	return (ret);
}
