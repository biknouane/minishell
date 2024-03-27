/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:07 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/03/27 07:57:08 by mbiknoua         ###   ########.fr       */
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
		return (1);
	if (strlen(*input) > 0)
		add_history(*input);
	return (0);
}

void	read_input(char **env)
{
	char	*input;
	t_list	*env_list;
	char	**env_tab;

	env_list = NULL;
	make_env_list(&env_list, env);
	while (1)
	{
		if (ft_readline(&input))
			continue ;
		break ;
	}
	// env_tab = make_env_tab(&env_list);
	// printf("HELLLLLL\n");
	// int	count = count_node(&env_list);
	// printf("this is count of the nodes: %d\n", count);
	// int i = 0;
	// while (env_tab[i])
	// {
	// 	printf("%s\n", env_tab[i]);
	// 	i++;
	// }
	// printf("%s", input);
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1 || *env == NULL)
		return (1);
	read_input(env);
}
