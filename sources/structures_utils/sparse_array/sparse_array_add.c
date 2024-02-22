/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_add.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:57:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

int	sparse_array_add(t_sparse_array *array, const void *elem)
{
	int		index;

	index = 0;
	if (array->size == array->capacity)
		if (sparse_array_growth(array))
			return (-1);
	while (array->indices[index] != -1)
		index++;
	array->indices[index] = array->size;
	ft_memcpy(array->buffer + array->size * array->elem_size,
		elem, array->elem_size);
	array->size++;
	return (index);
}

int	sparse_array_add_fast(t_sparse_array *array, const void *elem)
{
	if (array->size == array->capacity)
		if (sparse_array_growth(array))
			return (-1);
	array->indices[array->size] = array->size;
	ft_memcpy(array->buffer + array->size * array->elem_size,
		elem, array->elem_size);
	array->size++;
	return (array->size - 1);
}
