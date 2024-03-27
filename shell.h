/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:27 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/03/27 01:51:38 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}			t_list;

int		ft_isspace(char c);
int		ft_strisspace(char *line);
char	*ft_strchr(const char *s, int c);
int		ft_strlen(const char *s);
void	ft_strncpy(char *dest, const char *src, int n);
void	ft_strcpy(char *dest, const char *src);
int		ft_strcmp(char *env_var, char *str);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	split_env(t_list *env_list, char *str);
void	make_env_list(t_list **env_list, char **env);
t_list	*find_env(t_list **env_list, char *str);
void	add_to_env(t_list **env, char *key, char *value);
void	update_env(t_list **env, char *str);
void	del_env(t_list **env, char *str);
void	free_env(t_list	*tmp);
int		is_there_env(t_list **env_list, char *str);

#endif
