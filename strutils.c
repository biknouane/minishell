/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:01:57 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/01 23:37:20 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_atoi(char *str)
{
	int	sign;
	int	final_num;

	sign = 1;
	final_num = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if ((*str == '-') || (*str == '+'))
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		final_num = final_num * 10 + (*str - '0');
		str++;
	}
	return (final_num * sign);
}

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

char	*ft_strdup(const char *s1)
{
	size_t	str_len;
	char	*new_str;

	str_len = ft_strlen(s1);
	new_str = malloc(str_len + 1);
	if (!new_str)
		return (NULL);
	while (*s1)
	{
		*new_str = *s1;
		s1++;
		new_str++;
	}
	*new_str = '\0';
	return (new_str - str_len);
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
	if (!env_list->key)
		return ;
	env_list->value = ft_calloc(value_lenght + 1, sizeof(char));
	if (!env_list->value)
		return ;
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
		if (!tmp)
			return ;
		split_env(tmp, env[i]);
		ft_lstadd_back(env_list, tmp);
		i++;
	}
}

void	add_to_env(t_list **env, char *key, char *value)
{
	t_list	*tmp;

	tmp = ft_calloc(1, sizeof(t_list));
	if (!tmp)
		return ;
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
	if (!key)
		return ;
	ft_strncpy(key, str, str_lenght);
	tmp = find_env(env, key);
	if (tmp == NULL)
		return (free(key));
	str_lenght = ft_strlen(dilimiter +1);
	value = ft_calloc(str_lenght + 1, sizeof(char));
	if (!value)
		return ;
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

int	count_node(t_list **env)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = *env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*final_str;
	char	*temp_pointer;
	int		s_one_len;
	int		s_two_len;

	s_one_len = ft_strlen(s1);
	s_two_len = ft_strlen(s2);
	final_str = (char *)malloc(s_two_len + s_one_len + 1);
	if (!final_str)
		return (NULL);
	temp_pointer = final_str;
	while (*s1)
	{
		*temp_pointer = *s1;
		temp_pointer++;
		s1++;
	}
	while (*s2)
	{
		*temp_pointer = *s2;
		temp_pointer++;
		s2++;
	}
	*temp_pointer = '\0';
	return (final_str);
}

char	*make_var(t_list *node)
{
	char	*str;
	char	*tmp_one;

	tmp_one = ft_strjoin(node->key, "=");
	str = ft_strjoin(tmp_one, node->value);
	free(tmp_one);
	return (str);
}

char	**make_env_tab(t_list **env)
{
	t_list	*tmp;
	char	**tab;
	int		nodes_count;
	int		i;

	i = 0;
	tmp = *env;
	nodes_count = count_node(env);
	tab = (char **)ft_calloc(nodes_count + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	while (i < nodes_count)
	{
		tab[i] = make_var(tmp);
		tmp = tmp->next;
		i++;
	}
	return (tab);
}

void	print_error(char *str)
{
	printf("%s\n", str);
	exit(1);
}

int	ft_fork(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		print_error("fork");
	return (pid);
}

int	is_word_present(char *str, char *word)
{
	int	str_lenght;
	int	word_lenght;
	int	i;
	int	j;

	str_lenght = ft_strlen(str);
	word_lenght = ft_strlen(word);
	i = 0;
	while (i <= str_lenght - word_lenght)
	{
		j = 0;
		while (j < word_lenght)
		{
			if (str[i + j] != word[j])
				break ;
			j++;
		}
		if (j == word_lenght)
			return (1);
		i++;
	}
	return (0);
}

static	void	check_if_len_not_big(char const *s, int *str_len,
					size_t len, unsigned int start)
{
	*str_len = len;
	if (len > ft_strlen(s))
		*str_len = ft_strlen(s) - start;
	if (start >= ft_strlen(s))
		*str_len = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn_str;
	char	*temp_poi;
	char	*poi_on_s;
	int		str_len;

	check_if_len_not_big(s, &str_len, len, start);
	rtn_str = (char *)malloc(str_len + 1);
	if (!rtn_str)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		*rtn_str = '\0';
		return (rtn_str);
	}
	temp_poi = rtn_str;
	poi_on_s = (char *)(s + start);
	while (len && *poi_on_s)
	{
		*temp_poi = *poi_on_s;
		temp_poi++;
		poi_on_s++;
		len--;
	}
	*temp_poi = '\0';
	return (rtn_str);
}

static	int	count_words(char const *p, char c)
{
	char	*first_temp_pointer;
	char	*second_temp_pointer;
	int		counter;

	first_temp_pointer = (char *)p;
	second_temp_pointer = (char *)p;
	counter = 0;
	while (*first_temp_pointer)
	{
		second_temp_pointer++;
		if ((*first_temp_pointer != c && *second_temp_pointer == c)
			|| (*first_temp_pointer != c && *second_temp_pointer == '\0'))
			counter++;
		first_temp_pointer++;
	}
	return (counter);
}

static	void	allocate_word(char const *s, char **first_pointer
						, char **second_pointer, char c)
{
	while (*s && **first_pointer == c)
	{
		(*first_pointer)++;
		(*second_pointer)++;
	}
	while (*s && **second_pointer != c && **second_pointer != '\0')
		(*second_pointer)++;
}

char	**ft_split(char const *s, char c)
{
	char	**array_of_words;
	char	*begin_of_word;
	char	*end_of_word;
	int		num_of_words;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	begin_of_word = (char *)s;
	end_of_word = (char *)s;
	num_of_words = count_words(s, c);
	array_of_words = (char **)ft_calloc(sizeof(char *), num_of_words + 1);
	if (!array_of_words)
		return (NULL);
	while (num_of_words > i)
	{
		allocate_word(s, &begin_of_word, &end_of_word, c);
		array_of_words[i] = ft_substr(s, (int)(begin_of_word - s), \
				(end_of_word - begin_of_word));
		end_of_word++;
		begin_of_word = end_of_word;
		i++;
	}
	return (array_of_words);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
