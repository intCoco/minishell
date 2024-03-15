/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 11:43:52 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/15 18:47:21 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *m, int c, size_t l)
{
	size_t	i;

	i = 0;
	if (l == 0)
		return (NULL);
	while ((i < l - 1) && (((char *) m)[i] != ((char) c)))
		i++;
	if (((char *) m)[i] == (char) c)
		return ((char *)(m + i));
	return (NULL);
}
