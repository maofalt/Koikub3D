/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_destroy.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:02:06 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 18:02:51 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include <stdlib.h>

void	dynamic_array_destroy(t_dynamic_array *array)
{
	if (array != NULL)
	{
		free(array->buffer);
		free(array);
	}
}
