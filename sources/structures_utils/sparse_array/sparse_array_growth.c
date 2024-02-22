/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_growth.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:56:14 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

int	sparse_array_growth(t_sparse_array *array)
{
	void	*new_buffer;
	int		*new_indices;
	size_t	new_capacity;

	new_capacity = array->capacity * 2;
	new_buffer = ft_calloc(new_capacity, array->elem_size);
	new_indices = malloc(new_capacity * sizeof(new_indices[0]));
	if (new_buffer == NULL || new_indices == NULL)
	{
		free(new_buffer);
		free(new_indices);
		return (1);
	}
	ft_memset(new_indices, -1, new_capacity * sizeof(new_indices[0]));
	ft_memcpy(new_buffer, array->buffer, array->size * array->elem_size);
	free(array->buffer);
	free(array->indices);
	array->buffer = new_buffer;
	array->indices = new_indices;
	array->capacity = new_capacity;
	return (0);
}
