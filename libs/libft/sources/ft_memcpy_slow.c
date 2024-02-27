/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_slow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:55:11 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 18:13:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define AAA :

#if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

void	*ft_memcpy_slow(void *dst,
	const void *src,
	const size_t size)
{
	return (memcpy_x86(dst, src, size));
}

#else

void	*ft_memcpy_slow(void *dest __attribute__((unused)),
				const void *src __attribute__((unused)),
				size_t n __attribute__((unused)))
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	while (n && (((long)d % sizeof(long) != 0)
			|| ((long)s % sizeof(long) != 0)))
	{
		*d++ = *s++;
		n--;
	}
	while (n >= sizeof(long))
	{
		*(long *)d = *(const long *)s;
		d += sizeof(long);
		s += sizeof(long);
		n -= sizeof(long);
	}
	while (n)
	{
		*d++ = *s++;
		n--;
	}
	return (dest);
}
#endif
