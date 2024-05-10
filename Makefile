# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/08 19:55:55 by mbiknoua          #+#    #+#              #
#    Updated: 2024/05/10 22:39:36 by mbiknoua         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
FLAGS= -Wall -Wextra -Werror #-g -fsanitize=address


SCRC= chdir.c construct_tree_nodes.c del_env.c echo.c env.c execute_cmd.c \
exit.c expand_here_doc.c expand_nv_var.c export.c find_env.c finite_state_m.c free_env.c \
free_tree.c ft_atoi.c ft_calloc.c ft_lstadd_back.c ft_putendl_fd.c ft_split.c ft_strchr.c \
ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strncpy.c \
ft_substr.c get_token.c handle_here_doc.c look_ahead.c make_env_list.c make_env_tab.c \
parse_cmd.c parse_exec.c parse_pipe.c parse_redir.c print_error.c pwd.c search_path.c \
shell.c split_env.c str_is_space.c strip_string_quotes.c unset.c see_ahead.c


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