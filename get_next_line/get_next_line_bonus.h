/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 20:09:08 by mbiknoua          #+#    #+#             */
/*   Updated: 2022/11/23 18:45:29 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_file_infos
{
	int					fd;
	char				*str_holder;
	struct s_file_infos	*next;
}				t_file_infos;

char			*get_next_line(int fd);
t_file_infos	*my_lstnew_add_back(t_file_infos **lst, int fd);
char			*read_from_the_file(int fd, char *str_holder);
char			*return_the_line(char *str_holder);
void			my_lstdelone(t_file_infos **lst, t_file_infos *returned_node);
size_t			my_strlen(char *s);
char			*save_to_str_holder(char *str_holder);
int				my_strchr(char *s, int c);
void			process_final_str(char *s1, char *s2, char *temp_pointer);
char			*my_strjoin(char *str_holder, char *s2);
#endif