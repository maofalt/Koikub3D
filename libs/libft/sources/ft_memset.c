/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:09:38 by motero            #+#    #+#             */
/*   Updated: 2023/12/06 20:45:13 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

/*the function returns a void pointer, an address to a location in memory */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	long			long_c;

	ptr = (unsigned char *) s;
	long_c = (unsigned char) c;
	long_c |= long_c << 8;
	long_c |= long_c << 16;
	long_c |= long_c << 32;
	while (n && ((long)ptr & (sizeof(long) - 1)) != 0)
	{
		*ptr++ = c;
		n --;
	}
	while (n >= sizeof(long))
	{
		*(long *)ptr = long_c;
		ptr += sizeof(long);
		n -= sizeof(long);
	}
	while (n)
	{
		*ptr++ = c;
		n --;
	}
	return (s);
}
/*
[>void printArray(int arr[], int n)<]
[>{<]
   [>for (int i=0; i<n; i++)<]
      [>printf("%d ", arr[i]);<]
[>}<]

[>int	main()<]
[>{<]
	[>char str[50]= "GeeksforGekks is for programming geeks.";<]
	[>printf("\nBeforememset(): %s\n",str);<]

	[>//Fill8characters starting fo; str[13] with '.'<]
	[>memset(str + 13, '.', 8*sizeof(char));<]
	[>printf("\nAfter memset(): %s", str);<]
	[>char str1[50]= "GeeksforGekks is for programming geeks.";<]

	[>ft_memset(str1 + 13, '.', 8*sizeof(char));<]
	[>printf("\nAfter ft_memset(): %s", str1);<]

	[>int n = 10;<]
    [>int arr[10];<]

    [>// Fill whole array with 0.<]
    [>memset(arr, 0, n*sizeof(arr[0]));<]
    [>printf("\nArray after memset()\n");<]
    [>printArray(arr, n);<]

    [>int arr1[10];<]

    [>// Fill whole array with 0.<]
    [>ft_memset(arr1, 0, n*sizeof(arr1[0]));<]
    [>printf("\nArray after ft_memset\n");<]
    [>printArray(arr1, n);<]
    [>return 0;<]
[>}<]*/
