/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:55:11 by motero            #+#    #+#             */
/*   Updated: 2023/10/18 22:00:40 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <emmintrin.h>
#include <immintrin.h>

#if defined(__x86_64__) && defined(__SSE2__) && defined(__AVX__)

static void	*memcpy_x86(void *dest __attribute__((unused)),
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


static void *memcpy_sse2(void *dest, const void *src, size_t n) {
	char *d = dest;
	const char *s = src;

	printf("starting sse2\n");
	while ((((uintptr_t)d & 0xF) || ((uintptr_t)s & 0xF)) && n) {
		*d++ = *s++;
		n--;
	}
	size_t num_chunks = n / 16;

	asm volatile (
		"1:                             \n\t"
		"movdqa   (%1), %%xmm0          \n\t"
		"movdqa   %%xmm0, (%0)         \n\t"
		"add      $16, %0              \n\t"
		"add      $16, %1              \n\t"
		"dec      %2                   \n\t"
		"jnz      1b                   \n\t"
		: "+r"(d), "+r"(s), "+r"(num_chunks) // outputs
		:  // no separate inputs
		: "memory", "xmm0" // clobbers
	);
	n -= num_chunks * 16;
	while (n--)
		*d++ = *s++;
	return dest;
}

static void align_with_sse2(char **dest_ptr, const char **src_ptr, size_t *n_ptr) {
    char *d = *dest_ptr;
    const char *s = *src_ptr;
    size_t n = *n_ptr;

    // Align destination
    while ((uintptr_t)d & 0xF && n) {
        *d++ = *s++;
        n--;
    }

    // Align source using SSE2 if needed
    while ((uintptr_t)s & 0xF && n >= 16) {
        asm volatile (
            "movdqu (%1), %%xmm0      \n\t"
            "movdqu %%xmm0, (%0)     \n\t"
            : "+r"(d), "+r"(s)       // outputs
            :                        // no separate inputs
            : "memory", "xmm0"       // clobbers
        );
        d += 16;
        s += 16;
        n -= 16;
    }

    // Update the pointers
    *dest_ptr = d;
    *src_ptr = s;
    *n_ptr = n;
}

static void *memcpy_avx(void *dest, const void *src, size_t n) {
	char *d = dest;
	const char *s = src;

	//printf("starting avx\n");
	// If the destination is unaligned, we'll copy byte by byte
	// while ((((uintptr_t)d & 0x1F) || ((uintptr_t)s & 0x1F)) && n) {
	// 	*d++ = *s++;
	// 	n--;
	// }
	align_with_sse2(&d, &s, &n);
	
	if (!n)
		return dest;
	size_t num_chunks = (n / 32);
	asm volatile (
		"1:                             \n\t"
		"vmovdqa  (%1), %%ymm0          \n\t"
		"vmovdqa  %%ymm0, (%0)         \n\t"
		"add      $32, %0              \n\t"
		"add      $32, %1              \n\t"
		"dec      %2                   \n\t"
		"jnz      1b                   \n\t"
		: "+r"(d), "+r"(s), "+r"(num_chunks) // outputs
		:  // no separate inputs
		: "memory", "ymm0" // clobbers
	);
	n %= 32;
	while (n--)
		*d++ = *s++;
	return (dest);
}

void	*ft_memcpy(void *restrict dst,
	const void *restrict src,
	const size_t size)
{
	const int	use_x86_64 = size < 16;
	const int	use_sse2 = size >= 16 && size < 32;
	void		*(*chosen_memcpy)(void*, const void*, size_t);

	if (!src || !dst)
		return (NULL);
	chosen_memcpy = (void *(*)(void *, const void *, size_t))
		(use_x86_64 * (intptr_t)memcpy_x86
			+ use_sse2 * (intptr_t)memcpy_sse2
			+ (!use_x86_64 && !use_sse2) * (intptr_t)memcpy_avx);
	return (chosen_memcpy(dst, src, size));
}

#else

static void	copy_words(void	*restrict dst,
	const void *restrict src,
	size_t words)
{
	const uint64_t	*restrict	src64;
	uint64_t		*restrict	dst64;
	uint64_t					pages;
	uint64_t					offset;

	pages = words / 8;
	offset = words - pages * 8;
	src64 = (const uint64_t * restrict)src;
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
	const void *restrict src,
		size_t size)
{
	const uint64_t	*restrict	src64 = (const uint64_t * restrict)src;
	uint64_t		*restrict	dst64;

	dst64 = (uint64_t * restrict)dst;
	(void)size;
	*dst64 = *src64;
}

// Optimized memcpy implementation.
void	*ft_memcpy(void *restrict dst,
	const void *restrict src,
	const size_t size)
{
	const uint8_t	*restrict	src8;
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
		src8 = (const uint8_t * restrict)src;
		src8 = &src8[aligned_size];
		dst8 = (uint8_t * restrict)dst;
		dst8 = &dst8[aligned_size];
		while (offset--)
			*dst8++ = *src8++;
	}memcpy
	return (dst);
}
#endif
