/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strutils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 20:01:57 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/13 13:12:40 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	add_to_env(t_list **env, char *key, char *value)
{
	t_list	*tmp;

	tmp = ft_calloc(1, sizeof(t_list));
	if (!tmp)
		return ;
	tmp->key = key;
	tmp->value = value;
	ft_lstadd_back(env, tmp);
}

int	is_word_present(char *str, char *word)
{
	int	str_lenght;
	int	word_lenght;
	int	i;
	int	j;

	str_lenght = ft_strlen(str);
	word_lenght = ft_strlen(word);
	i = 0;
	while (i <= str_lenght - word_lenght)
	{
		j = 0;
		while (j < word_lenght)
		{
			if (str[i + j] != word[j])
				break ;
			j++;
		}
		if (j == word_lenght)
			return (1);
		i++;
	}
	return (0);
}
