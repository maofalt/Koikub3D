/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:56:56 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

void	sparse_array_remove(t_sparse_array *array, int index)
{
	int		index_in_buffer;

	if (index >= array->size || index < 0)
		return ;
	index_in_buffer = array->indices[index];
	if (index_in_buffer == -1)
		return ;
	ft_memmove(array->buffer + index_in_buffer * array->elem_size,
		array->buffer + (index_in_buffer + 1) * array->elem_size,
		(array->size - index - 1) * array->elem_size);
	array->size--;
	while (index < array->size)
	{
		if (array->indices[index] > index_in_buffer)
			array->indices[index]--;
		index++;
	}
	array->indices[index] = -1;
}
