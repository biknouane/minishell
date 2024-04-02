/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 08:26:25 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/01 22:03:16 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

typedef struct s_command
{
	int	type;
}				t_commad;

typedef struct s_exec_cmd
{
	int		type;
	char	*argv[20];
	char	*end_argv[20];
}				t_exec_cmd;

typedef struct s_redir_cmd
{
	int					type;
	char				*file;
	char				*end_file;
	int					mode;
	int					fd;
	struct s_command	*cmd;
}				t_redir_cmd;

typedef struct s_pipe_cmd
{
	int					type;
	struct s_command	*left_node;
	struct s_command	*right_node;
}				t_pipe_cmd;

t_commad	*construct_exec_node(void)
{
	
}
