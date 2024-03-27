/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:01:57 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/03/27 02:17:42 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\n')
		return (1);
	return (0);
}

int	ft_strisspace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
		if (!ft_isspace(line[i++]))
			return (0);
	return (1);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char) c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		s++;
		i++;
	}
	return (i);
}
void	ft_strcpy(char *dest, const char *src)
{
	while (*src)
	{
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';
}

void	ft_strncpy(char *dest, const char *src, int n)
{
	int	i;

	i = 0;
	while (i < n && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

int	ft_strcmp(char *env_var, char *str)
{
	while (*env_var)
	{
		if (*env_var != *str)
			return (0);
		env_var++;
		str++;
	}
	return (1);
}

void	ft_bzero(void *s, size_t n)
{
	while (n)
	{
		*(unsigned char *)s = '\0';
		s++;
		n--;
	}
	return ;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp_pointer;

	if (!lst || !new)
		return ;
	temp_pointer = *lst;
	if (*lst)
	{
		while (temp_pointer->next)
			temp_pointer = temp_pointer->next;
		temp_pointer->next = new;
	}
	else
		(*lst) = new;
}

void	split_env(t_list *env_list, char *str)
{
	char	*dilimiter;
	int		key_lenght;
	int		value_lenght;

	dilimiter = ft_strchr(str, '=');
	key_lenght = dilimiter - str;
	value_lenght = ft_strlen(dilimiter +1);
	env_list->key = ft_calloc(key_lenght + 1, sizeof(char));
	env_list->value = ft_calloc(value_lenght + 1, sizeof(char));
	ft_strncpy(env_list->key, str, key_lenght);
	ft_strcpy(env_list->value, dilimiter + 1);
}

void	make_env_list(t_list **env_list, char **env)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = NULL;
	while (env[i])
	{
		tmp = ft_calloc(1, sizeof(t_list));
		split_env(tmp, env[i]);
		ft_lstadd_back(env_list, tmp);
		i++;
	}
}

void	add_to_env(t_list **env, char *key, char *value)
{
	t_list	*tmp;

	tmp = ft_calloc(1, sizeof(t_list));
	tmp->key = key;
	tmp->value = value;
	ft_lstadd_back(env, tmp);
}

int	is_there_env(t_list **env_list, char *str)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, str))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

t_list	*find_env(t_list **env_list, char *str)
{
	t_list	*env_var;
	int		i;

	env_var = *env_list;
	i = 0;
	while (env_var)
	{
		if (ft_strcmp(env_var->key, str))
			return (env_var);
		env_var = env_var->next;
	}
	return (NULL);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	while (n && (*s1 || *s2))
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
		n--;
	}
	return (1);
}

void	update_env(t_list **env, char *str)
{
	char	*key;
	char	*value;
	char	*dilimiter;
	int		str_lenght;
	t_list	*tmp;

	key = NULL;
	value = NULL;
	dilimiter = ft_strchr(str, '=');
	str_lenght = dilimiter - str;
	key = ft_calloc(str_lenght + 1, sizeof(char));
	ft_strncpy(key, str, str_lenght);
	tmp = find_env(env, key);
	if (tmp == NULL)
	{
		free(key);
		return ;
	}
	str_lenght = ft_strlen(dilimiter +1);
	value = ft_calloc(str_lenght + 1, sizeof(char));
	ft_strcpy(value, dilimiter + 1);
	free(tmp->value);
	tmp->value = value;
}

void	free_env(t_list	*tmp)
{
	free(tmp->key);
	free(tmp->value);
	free(tmp);
	tmp = NULL;
}

void	del_env(t_list **env, char *str)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = *env;
	prev = NULL;
	if (!is_there_env(env, str))
		return ;
	if (tmp != NULL && ft_strcmp(tmp->key, str))
	{
		*env = tmp->next;
		free_env(tmp);
		return ;
	}
	while (tmp != NULL && !ft_strcmp(tmp->key, str))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free_env(tmp);
}
