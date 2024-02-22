/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_growth.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:09:24 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:54:31 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include <libft.h>

void	*dynamic_array_growth(t_dynamic_array *array)
{
	void	*new_buffer;

	new_buffer = ft_calloc(array->capacity * 2, array->elem_size);
	if (new_buffer == NULL)
		return (NULL);
	ft_memcpy(new_buffer, array->buffer, array->size * array->elem_size);
	free(array->buffer);
	array->buffer = new_buffer;
	array->capacity *= 2;
	return (array->buffer);
}
