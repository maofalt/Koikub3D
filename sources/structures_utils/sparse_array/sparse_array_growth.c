/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_growth.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 21:33:58 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"
#include "draw_utils.h"

int	sparse_array_growth(t_sparse_array *array)
{
	void	*new_buffer;
	int		*new_indices;
	size_t	new_capacity;

	new_capacity = array->capacity * 2;
	new_buffer = aligned_calloc(new_capacity, array->elem_size, 32);
	new_indices = aligned_malloc(new_capacity * sizeof(new_indices[0]), 32);
	if (new_buffer == NULL || new_indices == NULL)
	{
		aligned_free(new_buffer);
		aligned_free(new_indices);
		return (1);
	}
	ft_memset(new_indices, -1, new_capacity * sizeof(new_indices[0]));
	ft_memcpy(new_buffer, array->buffer, array->size * array->elem_size);
	aligned_free(array->buffer);
	aligned_free(array->indices);
	array->buffer = new_buffer;
	array->indices = new_indices;
	array->capacity = new_capacity;
	return (0);
}
