/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:07 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/04/26 18:00:03 by mbiknoua         ###   ########.fr       */
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
	// char	**env_tab;

	env_list = NULL;
	make_env_list(&env_list, env);
	while (ft_readline(&input))
	{
		// if is a builting
			// continue ;
		if (fork() == 0)
		{
			tree = parse_cmd(input);
			expand(tree);
			run_cmd(tree);
		}
		wait(0);
	}
	exit(0);
	// ft_export(&env_list, input);
	// t_list *tmp = env_list;
	// while (tmp)
	// {
	// 	printf("%s=%s\n", tmp->key, tmp->value);
	// 	tmp = tmp->next;
	// }
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1 || *env == NULL)
		return (1);
	read_input(env);
}
