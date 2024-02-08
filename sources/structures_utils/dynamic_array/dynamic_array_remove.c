/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_remove.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:58:07 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:55:12 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "libft.h"

void	dynamic_array_remove(t_dynamic_array *array, size_t index)
{
	if (index >= array->size)
		return ;
	ft_memmove(array->buffer + (index * array->elem_size),
		array->buffer + ((index + 1) * array->elem_size),
		(array->size - index - 1) * array->elem_size);
	array->size--;
}
