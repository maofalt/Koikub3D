/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:55:11 by motero            #+#    #+#             */
/*   Updated: 2023/10/17 04:27:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef __x86_64__

void	*ft_memcpy(void *dest __attribute__((unused)),
				const void *src __attribute__((unused)),
				size_t n __attribute__((unused)))
{
	asm volatile (
		"cld;"
		"mov %rdx, %rcx;"
		"rep movsb"
	);
	return (dest);
}
#else

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
