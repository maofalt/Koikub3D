/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:02:06 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:02:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include <stdlib.h>

t_dynamic_array	*dynamic_array_init(size_t elem_size, size_t capacity)
{
	t_dynamic_array	*array;

	array = malloc(sizeof(t_dynamic_array));
	if (array == NULL)
		return (NULL);
	array->elem_size = elem_size;
	array->size = 0;
	array->capacity = capacity;
	array->buffer = calloc(capacity, elem_size);
	if (array->buffer == NULL)
	{
		free(array);
		return (NULL);
	}
	return (array);
}
