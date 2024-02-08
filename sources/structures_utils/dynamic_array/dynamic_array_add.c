/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_add.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:10:22 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:54:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "libft.h"

void	*dynamic_array_add(t_dynamic_array *array, void *element)
{
	if (array->size == array->capacity)
	{
		if (dynamic_array_growth(array) == NULL)
			return (NULL);
	}
	ft_memcpy(array->buffer + (array->size * array->elem_size),
		element, array->elem_size);
	array->size++;
	return (array->buffer);
}
