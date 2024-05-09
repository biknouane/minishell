/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:07 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/10 00:14:55 by mbiknoua         ###   ########.fr       */
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
	if (ft_strcmp(*input, "") == 0 || ft_str_is_space(*input))
		return (0);
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (1);
}

void	read_input(char **env)
{
	t_param_holder	params;
	t_command		*tree;
	char			**env_tab;

	params.exit_status = 0;
	params.env_list = NULL;
	*(params.state) = NORMAL;
	make_env_list(&(params.env_list), env);
	while (ft_readline(&(params.input)))
	{
		tree = parse_cmd(&params);
		env_tab = make_env_tab(&(params.env_list));
		execute_cmd(tree, env_tab, &(params.exit_status));
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
