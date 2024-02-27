/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 18:37:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"
#include "draw_utils.h"

void	sparse_array_destroy(t_sparse_array *array)
{
	if (array == NULL)
		return ;
	aligned_free(array->indices);
	aligned_free(array->buffer);
	aligned_free(array);
}
