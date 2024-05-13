/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:58:07 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 01:11:56 by mbiknoua         ###   ########.fr       */
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
	if (ft_strcmp(*input, "") || ft_str_is_space(*input))
	{
		free(*input);
		return (1);
	}
	if (ft_strlen(*input) > 0)
		add_history(*input);
	return (0);
}

void	read_input(char **env)
{
	t_param_holder	*params;
	t_command		*tree;
	char			*tmp;
	// char			**env_tab;

	params = (t_param_holder *) ft_calloc(1, sizeof(t_param_holder));
	params->exit_status = 0;
	params->env_list = NULL;
	params->state = NORMAL;
	tree = NULL;
	make_env_list(&(params->env_list), env);
	while (1)
	{
		if (ft_readline(&params->input))
			continue ;
		tmp = params->input;
		tree = parse_cmd(params);
		if (!(params->is_error))
			execute_cmd(tree, &(params->env_list), &(params->exit_status));
		params->is_error = 0;
		free_tree(tree);
		free(tmp);
		system("leaks minishell");
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	if (ac != 1 || *env == NULL)
		return (1);
	read_input(env);
}
