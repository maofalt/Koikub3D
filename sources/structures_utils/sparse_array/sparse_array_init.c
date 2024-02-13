/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:55:21 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

t_sparse_array	*sparse_array_init(size_t elem_size, size_t capacity)
{
	t_sparse_array	*array;

	array = malloc(sizeof(t_sparse_array));
	if (array == NULL)
		return (NULL);
	array->elem_size = elem_size;
	array->size = 0;
	array->capacity = capacity;
	array->indices = malloc(capacity * sizeof(array->indices[0]));
	array->buffer = ft_calloc(capacity, elem_size);
	if (array->indices == NULL || array->buffer == NULL)
	{
		free(array->indices);
		free(array->buffer);
		free(array);
		return (NULL);
	}
	ft_memset(array->indices, -1, capacity * sizeof(array->indices[0]));
	return (array);
}
