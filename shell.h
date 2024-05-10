/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:27 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 17:04:45 by mbiknoua         ###   ########.fr       */
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
	char	**argv;
}				t_exec_cmd;

typedef struct s_redir_cmd
{
	t_cmd				type;
	char				*file;
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

typedef struct s_param_holder
{
	char		*input;
	char		*end_str;
	t_list		*env_list;
	t_state		state;
	int			is_error;
	int			exit_status;
}				t_param_holder;

char		*expand_nv_var(char *str, t_list **env_list);
int			strip_string_quotes(char *str, int *single_q_n, int *double_q_n);
void		parse_string(t_param_holder *params);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**ft_split(char const *s, char c);
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

int			ft_export(t_list **env, char **str);

t_command	*construct_pipe_node(t_command *left_node, \
						t_command *right_node);
t_command	*construct_redir_node(t_command *sub_node, \
						char	*file, int mode, int fd);
t_command	*construct_exec_node(void);
t_token		get_token(t_param_holder *params, char **str_ret);
int			print_error(char *error);
void		free_tree(t_command *tree);

// this is the part for the parsing
t_command	*parse_pipe(t_param_holder *params);
t_command	*parse_exec(t_param_holder *params);
t_command	*parse_redir(t_command *cmd, t_param_holder *params);
t_command	*parse_cmd(t_param_holder *params);
int			look_ahead(t_param_holder *params, char *tokens);
int			see_ahead(char *str, char *tokens);

// this is the part for here_doc function
char		*expand_her_doc(char *str, t_list **env_list);
int			her_doc(char *eof, int fd, t_list *env_list);

// this is the part for the execution
void		execute_cmd(t_command *tree, char **env_tab, int *exit_status);
#endif
