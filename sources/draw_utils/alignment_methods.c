/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:30 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	*aligned_malloc(size_t size, size_t alignment)
{
	void	*original_ptr;
	char	*aligned_ptr;

	original_ptr = malloc(size + alignment + sizeof(void *));
	if (!original_ptr)
		return (NULL);
	aligned_ptr = (char *)original_ptr + sizeof(void *);
	aligned_ptr += alignment - ((uintptr_t)aligned_ptr & (alignment - 1));
	((void **)aligned_ptr)[-1] = original_ptr;
	return (aligned_ptr);
}

void	aligned_free(void	*ptr)
{
	void	*original_ptr;

	if (!ptr)
		return ;
	original_ptr = ((void **)ptr)[-1];
	free(original_ptr);
}

void	*aligned_calloc(size_t nmemb, size_t size, size_t alignment)
{
	void	*ptr;

	if (nmemb == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	if (!nmemb || !size)
	{
		ptr = aligned_malloc(sizeof(void) * 1, alignment);
		if (!ptr)
			return (NULL);
		ft_bzero(ptr, 1);
		return (ptr);
	}

	ptr = aligned_malloc(nmemb * size, alignment);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
