/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiknoua <mbiknoua@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 05:09:24 by mbiknoua          #+#    #+#             */
/*   Updated: 2024/05/18 14:08:29 by mbiknoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static	void	check_if_len_not_big(char const *s, int *str_len,
					size_t len, unsigned int start)
{
	*str_len = len;
	if ((int)len > ft_strlen(s))
		*str_len = ft_strlen(s) - start;
	if (start >= (unsigned int)ft_strlen(s))
		*str_len = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn_str;
	char	*temp_poi;
	char	*poi_on_s;
	int		str_len;

	check_if_len_not_big(s, &str_len, len, start);
	rtn_str = (char *)malloc(str_len + 1);
	if (!rtn_str)
		exit (1);
	if (start >= (unsigned int)ft_strlen(s))
	{
		*rtn_str = '\0';
		return (rtn_str);
	}
	temp_poi = rtn_str;
	poi_on_s = (char *)(s + start);
	while (len && *poi_on_s)
	{
		*temp_poi = *poi_on_s;
		temp_poi++;
		poi_on_s++;
		len--;
	}
	*temp_poi = '\0';
	return (rtn_str);
}
