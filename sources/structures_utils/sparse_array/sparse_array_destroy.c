/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sparse_array_destroy.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:26:14 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/13 02:58:06 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "sparse_array.h"
#include "libft.h"

void	sparse_array_destroy(t_sparse_array *array)
{
	if (array == NULL)
		return ;
	free(array->indices);
	free(array->buffer);
	free(array);
}
