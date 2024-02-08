/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_new_element.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:10:22 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 22:45:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include <stdlib.h>

void	*dynamic_array_new_element(t_dynamic_array *array)
{
	void	*new_elem_ptr;

	if (array->size == array->capacity)
	{
		if (dynamic_array_growth(array) == NULL)
			return (NULL);
	}
	new_elem_ptr = array->buffer + (array->size * array->elem_size);
	array->size++;
	return (new_elem_ptr);
}
