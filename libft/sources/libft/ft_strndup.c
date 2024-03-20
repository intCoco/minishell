/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 17:01:54 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/20 17:02:20 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strndup(char *src, int min, int max)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *) malloc((max - min) + 1);
	if (!dest)
		return (NULL);
	while (min < max)
	{
		dest[i] = src[min];
		min++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}