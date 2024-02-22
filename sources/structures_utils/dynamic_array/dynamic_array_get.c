/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_get.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:03:27 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:54:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"

void	*dynamic_array_get(t_dynamic_array *array, size_t index)
{
	if (index >= array->size)
		return (NULL);
	return (array->buffer + (index * array->elem_size));
}
