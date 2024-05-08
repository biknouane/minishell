/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:27 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 13:17:14 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "readline/readline.h"
# include "readline/history.h"

typedef struct s_list
{
	int				print_with_env;
	char			*key;
	char			*value;
	struct s_list	*next;
}			t_list;

typedef enum s_cmd
{
	EXEC,
	REDIR,
	PIPE
}			t_cmd;

typedef enum s_token
{
	PIP = 124,
	RE_IN = 60,
	RE_OUT = 62,
	H_DOK = 45,
	APEND = 43,
	WORD = 97
}			t_token;

typedef enum s_state
{
	NORMAL,
	IN_SINGL_QUOTE,
	IN_DOUBLE_QUOTE
}			t_state;

typedef struct s_command
{
	t_cmd	type;
}				t_command;

typedef struct s_exec_cmd
{
	t_cmd	type;
	char	*argv[100];
	// char	*end_argv[20];
}				t_exec_cmd;

typedef struct s_redir_cmd
{
	t_cmd				type;
	char				*file;
	char				*end_file;
	int					mode;
	int					fd;
	struct s_command	*cmd;
}				t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_cmd				type;
	struct s_command	*left_node;
	struct s_command	*right_node;
}				t_pipe_cmd;

char		*expand_nv_var(char *str, t_list **env_list);
int			strip_string_quotes(char *str);
void		parse_string(char **str, t_state *state);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(char *str);
int			ft_str_is_space(char *line);
char		*ft_strchr(const char *s, int c);
int			ft_strlen(const char *s);
void		ft_strncpy(char *dest, const char *src, int n);
void		ft_strcpy(char *dest, const char *src);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
int			ft_strcmp(char *env_var, char *str);
void		ft_putchar_fd(char c, int fd);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
void		*ft_calloc(size_t count, size_t size);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		split_env(t_list *env_list, char *str);
void		make_env_list(t_list **env_list, char **env);
t_list		*find_env(t_list **env_list, char *str);
void		del_env(t_list **env, char *str);
void		free_env(t_list	*tmp);
char		**make_env_tab(t_list **env);
int			count_node(t_list **env);
char		*make_var(t_list *node);

int			ft_export(t_list **env, char *str);

t_command	*construct_pipe_node(t_command *left_node, \
						t_command *right_node);
t_command	*construct_redir_node(t_command *sub_node, \
						char	*file, int mode, int fd);
t_command	*construct_exec_node(void);
t_token		get_token(char	**str, char *end_str, char **str_ret, t_state *state);

#endif
