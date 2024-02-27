/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:02:06 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 18:29:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "draw_utils.h"
#include <stdlib.h>

void	dynamic_array_destroy(t_dynamic_array *array)
{
	if (array != NULL)
	{
		aligned_free(array->buffer);
		aligned_free(array);
	}
}
