/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_get.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:56:01 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

void	*sparse_array_get(t_sparse_array *array, int index)
{
	int		index_in_buffer;

	if (index >= array->size || index < 0)
		return (NULL);
	index_in_buffer = array->indices[index];
	if (index_in_buffer == -1)
		return (NULL);
	return (array->buffer + index_in_buffer * array->elem_size);
}
