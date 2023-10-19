/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:55:11 by motero            #+#    #+#             */
/*   Updated: 2023/10/20 01:13:53 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <emmintrin.h>
#include <immintrin.h>
#define AAA :

#if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

static inline void	align_memory_sse_asm(char **d,  char **s, size_t *n)
{
	asm	volatile
		(
			"movdqu  (%1), %%xmm0\n\t"
			"movdqu  %%xmm0, (%0)\n\t"
			"add     $16, %0\n\t"
			"add     $16, %1\n\t"
			"sub     $16, %2\n\t"
			AAA "+r"(*d), "+r"(*s), "+r"(*n)
			);
}

static inline void	align_memory_sse(char **d,  char **s, size_t *n)
{
	while ((((uintptr_t) * d & 0x1F) || ((uintptr_t) * s & 0x1F)) && *n >= 16)
	{
		align_memory_sse_asm(d, s, n);
	}
}

static inline void	copy_chunks_avx_asm(char **d,
	 char **s,
	size_t *num_chunks)
{
	asm	volatile (
			"1:                             \n\t"
			"vmovdqa  (%1), %%ymm0          \n\t"
			"vmovntdq  %%ymm0, (%0)         \n\t"
			"add      $32, %0              \n\t"
			"add      $32, %1              \n\t"
			"dec      %2                   \n\t"
			"jnz      1b                   \n\t"
			"sfence						   \n\t"
			AAA "+r"(*d), "+r"(*s), "+r"(num_chunks)
			AAA
			AAA "memory", "ymm0");
}

static inline void	copy_chunks_avx(char **d,  char **s, size_t *n)
{
	size_t	num_chunks;

	num_chunks = (*n >> 5);
	copy_chunks_avx_asm(d, s, &num_chunks);
	*n %= 32;
}

static void	*memcpy_avx(void *dest,  void *src, size_t n)
{
	char		*d;
	 char	*s = src;

	d = dest;
	align_memory_sse(&d, &s, &n);
	if (!n)
		return (dest);
	copy_chunks_avx(&d, &s, &n);
	while (n--)
		*(d)++ = *(s)++;
	return (dest);
}

void	*ft_memcpy(void *restrict dst,
	 void *restrict src,
	 size_t size)
{
	 size_t	src_alignment_offset = ((uintptr_t)src & 0x1F);
	 size_t	dst_alignment_offset = ((uintptr_t)dst & 0x1F);

	if (!src || !dst)
		return (NULL);
	if (size > 32 && src_alignment_offset < 1 && dst_alignment_offset < 1)
		return (memcpy_avx(dst, src, size));
	return (memcpy_x86(dst, src, size));
}

#else

static void	copy_words(void	*restrict dst,
	 void *restrict src,
	size_t words)
{
	 uint64_t	*restrict	src64;
	uint64_t		*restrict	dst64;
	uint64_t					pages;
	uint64_t					offset;

	pages = words / 8;
	offset = words - pages * 8;
	src64 = ( uint64_t * restrict)src;
	dst64 = (uint64_t * restrict)dst;
	while (pages--)
	{
		*dst64++ = *src64++;
		*dst64++ = *src64++;
		*dst64++ = *src64++;
		*dst64++ = *src64++;
		*dst64++ = *src64++;
		*dst64++ = *src64++;
		*dst64++ = *src64++;
		*dst64++ = *src64++;
	}
	while (offset--)
		*dst64++ = *src64++;
}

// Copy small memory chunks (8 bytes or less).
static void	copy_small(void *restrict dst,
	 void *restrict src,
		size_t size)
{
	 uint64_t	*restrict	src64 = ( uint64_t * restrict)src;
	uint64_t		*restrict	dst64;

	dst64 = (uint64_t * restrict)dst;
	(void)size;
	*dst64 = *src64;
}

// Optimized memcpy implementation.
void	*ft_memcpy(void *restrict dst,
	 void *restrict src,
	 size_t size)
{
	 uint8_t	*restrict	src8;
	uint8_t			*restrict	dst8;
	size_t						offset;
	size_t						words;
	size_t						aligned_size;

	if (!src || !dst)
		return (NULL);
	if (size <= 8)
		return (copy_small(dst, src, size), dst);
	words = size / 8;
	aligned_size = words * 8;
	offset = size - aligned_size;
	copy_words(dst, src, words);
	if (offset)
	{
		src8 = ( uint8_t * restrict)src;
		src8 = &src8[aligned_size];
		dst8 = (uint8_t * restrict)dst;
		dst8 = &dst8[aligned_size];
		while (offset--)
			*dst8++ = *src8++;
	}memcpy
	return (dst);
}
#endif
