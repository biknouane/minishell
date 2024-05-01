/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:07 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/01 23:38:47 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int	ft_readline(char **input)
{
	*input = readline("minishell: ==> ");
	if (!*input)
	{
		printf("exit\n");
		exit(1);
	}
	if (strcmp(*input, "") == 0 || ft_strisspace(*input))
		return (0);
	if (strlen(*input) > 0)
		add_history(*input);
	return (1);
}

void	read_input(char **env)
{
	char		*input;
	t_command	*tree;
	t_list		*env_list;
	char		**env_tab;

	env_list = NULL;
	make_env_list(&env_list, env);
	while (ft_readline(&input))
	{
		// if is a builting
			// continue ;
		if (fork() == 0)
		{
			env_tab = make_env_tab(env_list);
			tree = parse_cmd(input, env_tab);
			run_cmd(tree, env_tab);
		}
		wait(0);
	}
	exit(0);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1 || *env == NULL)
		return (1);
	read_input(env);
}
