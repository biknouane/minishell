/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 07:56:10 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/04 06:01:23 by mbiknoua         ###   ########.fr       */
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

// this is the alternative of execve of builtings
void	handle_builtin(char	*cmd, char **args)
{
	char	*tmp;

	if (ft_strcmp(cmd, "echo"))
	{
		if (!print_echo_args(*args[1]))
			printf("\n");
	}
}

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
		printf("declare -x %s =\"", var->key);
		if (var->value)
			printf("%s", var->value);
		printf("\"\n");
		var = var->next;
	}
}

// this function handles the export builtin and coudld handle multiple args
int	ft_export(t_list **env, char *str)
{
	t_list	*var;

	if (str)
	{
		if (is_valid_var(str))
		{
			var = ft_calloc(1, sizeof(t_list));
			split_env(var, str);
			ft_lstadd_back(env, var);
		}
		// else
		// print an error and return to minishell
		// return (-1);
	}
	else
		handle_print_export(env);
	return (0);
}

int	ft_unset(t_list **env, char *str)
{
	del_env(env, str);
}

int	ft_env(t_list **env)
{
	t_list	*tmp;

	tmp = *env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_exit(char *str)
{
	int	num;

	num = ft_atoi(str);
	exit(num);
}

int	ft_chdir(t_list **env_list, char *str)
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

int	ft_pwd(t_list **env_list)
{
	t_list	*tmp;

	tmp = find_env(env_list, "PWD");
	printf("%s\n", tmp->value);
}
