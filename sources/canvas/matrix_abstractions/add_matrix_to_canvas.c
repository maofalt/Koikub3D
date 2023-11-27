/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_events.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/10/10 19:28:18 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

int	apply_matrix_transformation(t_canvas *canvas, t_matrix3x3 matrix)
{
	printf("apply_matrix_transformation\n");
	if (push_matrix_op(&canvas->matrix_operations,
			matrix))
		return (1);
	printf("Matrix applied and pushed\n");
	canvas->transformation_matrix = matrix_multiply(
			canvas->transformation_matrix, matrix);
	printf("Matrix multiplied\n");
	return (0);
}