# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 19:55:55 by mbiknoua          #+#    #+#              #
#    Updated: 2024/03/17 20:36:23 by mbiknoua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
FLAGS= -Wall -Wextra -Werror -g -fsanitize=address


SCRC= shell.c strutils.c


OBJ= $(SCRC:.c=.o)
HEADER= shell.h
READLINE_HEADER= /goinfre/mbiknoua/homebrew/opt/readline/include
READLINE_LIB= /goinfre/mbiknoua/homebrew/opt/readline/lib




all: $(NAME)


$(NAME): $(OBJ)
	@cc $(FLAGS) $^  -L $(READLINE_LIB) -lreadline -o $@  

%.o: %.c $(HEADER)
	@cc $(FLAGS) -c $< -o $@  -I $(READLINE_HEADER)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all


.PHONY: all fclean clean re bonus%