/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:08:27 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/07 05:08:54 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	int	count_words(char const *p, char c)
{
	char	*first_temp_pointer;
	char	*second_temp_pointer;
	int		counter;

	first_temp_pointer = (char *)p;
	second_temp_pointer = (char *)p;
	counter = 0;
	while (*first_temp_pointer)
	{
		second_temp_pointer++;
		if ((*first_temp_pointer != c && *second_temp_pointer == c)
			|| (*first_temp_pointer != c && *second_temp_pointer == '\0'))
			counter++;
		first_temp_pointer++;
	}
	return (counter);
}

static	void	allocate_word(char const *s, char **first_pointer
						, char **second_pointer, char c)
{
	while (*s && **first_pointer == c)
	{
		(*first_pointer)++;
		(*second_pointer)++;
	}
	while (*s && **second_pointer != c && **second_pointer != '\0')
		(*second_pointer)++;
}

char	**ft_split(char const *s, char c)
{
	char	**array_of_words;
	char	*begin_of_word;
	char	*end_of_word;
	int		num_of_words;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	begin_of_word = (char *)s;
	end_of_word = (char *)s;
	num_of_words = count_words(s, c);
	array_of_words = (char **)ft_calloc(sizeof(char *), num_of_words + 1);
	if (!array_of_words)
		return (NULL);
	while (num_of_words > i)
	{
		allocate_word(s, &begin_of_word, &end_of_word, c);
		array_of_words[i] = ft_substr(s, (int)(begin_of_word - s), \
				(end_of_word - begin_of_word));
		end_of_word++;
		begin_of_word = end_of_word;
		i++;
	}
	return (array_of_words);
}
