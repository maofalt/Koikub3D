/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 23:48:04 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/19 22:33:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdio.h>

double	random_double(void)
{
	static unsigned int	seed = 123456789;

	seed = seed * 1103515245 + 12345;
	return ((double)(seed & 0x7fffffff) / 0x7fffffff);
}

uint32_t	xorshift32(void)
{
	static uint32_t	x = 123456789;

	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return (x);
}

//random double between 0 and 1
double	random_double_xorshift32(void)
{
	return ((double)xorshift32() / 0xFFFFFFFF);
}
