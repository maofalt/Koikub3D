/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_x86.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:55:11 by motero            #+#    #+#             */
/*   Updated: 2023/10/20 01:12:24 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <emmintrin.h>
#include <immintrin.h>
#define AAA :

#if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

void	*memcpy_x86(void *dest __attribute__((unused)),
				const void *src __attribute__((unused)),
				size_t n __attribute__((unused)))
{
	asm volatile (
		"cld;"
		"mov %rdx, %rcx;"
		"rep movsb;"
	);
	return (dest);
}

#endif
