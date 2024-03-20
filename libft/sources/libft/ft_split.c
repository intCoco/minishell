/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:28:45 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/20 17:06:05 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_splitcount(const char *s, char *charset)
{
	int	i;
	int	len;
	int	start;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] && ft_ischarset(s[i], charset))
			i++;
		start = i;
		while (s[i] && !ft_ischarset(s[i], charset))
			i++;
		if (i != start)
			len++;
	}
	return (len);
}

char	**ft_split(char const *s, char *charset)
{
	size_t	i;
	size_t	j;
	size_t	start;
	char	**res;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (ft_splitcount(s, charset) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		while (ft_ischarset(s[i], charset))
			i++;
		start = i;
		while (!ft_ischarset(s[i], charset) && s[i])
			i++;
		if (i != start && (ft_ischarset(s[i], charset) || s[i] == '\0'))
			res[++j] = ft_strndup((char *)s, start, i);
	}
	res[ft_splitcount(s, charset)] = 0;
	return (res);
}
