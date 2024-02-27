/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 23:02:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"
#include "draw_utils.h"

t_sparse_array	*sparse_array_init(size_t elem_size, size_t capacity)
{
	t_sparse_array	*array;

	array = aligned_malloc(sizeof(t_sparse_array), 32);
	if (array == NULL)
		return (NULL);
	array->elem_size = elem_size;
	array->size = 0;
	array->capacity = capacity;
	array->indices = aligned_malloc(capacity * sizeof(array->indices[0]), 32);
	array->buffer = aligned_calloc(capacity, elem_size, 32);
	if (array->indices == NULL || array->buffer == NULL)
	{
		aligned_free(array->indices);
		aligned_free(array->buffer);
		aligned_free(array);
		return (NULL);
	}
	ft_memset(array->indices, -1, capacity * sizeof(array->indices[0]));
	return (array);
}
