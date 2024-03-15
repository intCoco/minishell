/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chuchard <chuchard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:23:13 by chuchard          #+#    #+#             */
/*   Updated: 2024/03/15 18:54:44 by chuchard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../includes/libft.h"

#define MAX 2147483647

#define MULT 48271
#define MOD 2147483647

size_t	ft_intlen(int n)
{
	int	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	my_rand(int32_t seed)
{
	int32_t	hi;
	int32_t	lo;

	hi = seed / (MOD / MULT);
	lo = seed % (MOD / MULT);
	seed = MULT * lo - (MOD % MULT) * hi;
	if (seed < 0)
		seed += MOD;
	return ((int)((double)seed / MOD * MAX));
}

int	ft_random(int max)
{
	static int	nb;
	int			fd;
	char		str[30];

	if (nb == 0)
	{
		fd = open("save.txt", O_RDWR);
		read(fd, str, 30);
		close(fd);
		nb = my_rand(ft_atoi(str));
	}
	else
		nb = my_rand(nb);
	fd = open("save.txt", O_RDWR);
	write(fd, &nb, ft_intlen(nb));
	close(fd);
	return (nb % (max + 1));
}
