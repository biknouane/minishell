/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:27 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/17 16:17:43 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include "readline/readline.h"
# include "get_next_line/get_next_line.h"
# include "readline/history.h"

int	forcked;

// this struct is tmp struct to hold some values 
// for the strip_string_quotes function
typedef struct s_strip_quotes
{
	int	i;
	int	j;
	int	sin_q;
	int	doub_q;
}				t_strip_quotes;

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
	t_cmd		type;
	char		*file;
	int			mode;
	int			fd;
	t_command	*cmd;
}				t_redir_cmd;

typedef struct s_pipe_cmd
{
	t_cmd		type;
	t_command	*left_node;
	t_command	*right_node;
}				t_pipe_cmd;

typedef struct s_param_holder
{
	char		*input;
	char		*end_str;
	t_list		*env_list;
	t_state		state;
	int			is_error;
	int			exit_status;
	int			*fd_table;
	int			*files_table;
	int			fd_index;
	int			is_pipe;
	int			read_in;
}				t_param_holder;

void		ft_putnbr_fd(int n, int fd);
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
void		update_env(t_list **env, char *str);
char		**make_env_tab(t_list **env);

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
void	update_exit_status(int *exit_status);

// this is the part for here_doc function
void		expand_her_doc(char *str, t_list **env_list, int fd);
int			her_doc(char *eof, int fd, t_param_holder *params);

// this is the part for the execution
void		execute_cmd(t_command *tree, t_param_holder *params);

void		search_cmd(t_list *node, char **cmd);
int			handle_builtin(char	*cmd, char **args, t_list **env_list);

/******** builting      *********/

int			print_echo_args(char **args);
int			ft_exit(char **str);
int			ft_pwd(void);
int			ft_env(t_list **env);
int			ft_chdir(t_list **env_list, char **str);
int			ft_unset(t_list **env, char **str);
int			ft_export(t_list **env, char **str);



/*************        */
int get_key_length(char *str);
char	*expand(char *str, t_param_holder *params);
int	is_directory(char *path);
#endif
