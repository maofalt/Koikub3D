/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_growth.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:09:24 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 21:32:37 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include <libft.h>
#include "draw_utils.h"

void	*dynamic_array_growth(t_dynamic_array *array)
{
	void	*new_buffer;

	new_buffer = aligned_calloc(array->capacity * 2, array->elem_size, 32);
	if (new_buffer == NULL)
		return (NULL);
	ft_memcpy(new_buffer, array->buffer, array->size * array->elem_size);
	aligned_free(array->buffer);
	array->buffer = new_buffer;
	array->capacity *= 2;
	return (array->buffer);
}
