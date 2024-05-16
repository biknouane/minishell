/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 23:16:54 by mbiknoua          #+#    #+#             */
/*   Updated: 2022/11/23 18:50:58 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	my_strlen(char *s);
char	*save_to_str_holder(char *str_holder);
int		my_strchr(char *s, int c);
void	process_final_str(char *s1, char *s2, char *temp_pointer);
char	*my_strjoin(char *s1, char *s2);
char	*return_the_line(char *str_holder);
char	*read_from_the_file(int fd, char *str_holder);
#endif