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
	if (push_matrix_op(&canvas->matrix_operations,
			matrix))
		return (1);
	canvas->transformation_matrix = matrix_multiply(
			canvas->transformation_matrix, matrix);
	return (0);
}

//apply zoom centered in  a given position 
int	apply_zoom_at_position(t_canvas *canvas, double zoom, t_point2i pos)
{
	t_matrix3x3	translation;
	t_matrix3x3	zoom_matrix;
	t_matrix3x3	translation_back;

	(void)zoom;
	translation = translation_matrix((t_point2d){{pos.x, pos.y}});
	// if (apply_matrix_transformation(canvas, translation))
	// 	return (1);
	zoom_matrix = scaling_matrix((t_point2d){{zoom, zoom}});
	if (apply_matrix_transformation(canvas, zoom_matrix))
		return (1);
	translation_back = translation_matrix((t_point2d){{-pos.x, -pos.y}});
	// if (apply_matrix_transformation(canvas, translation_back))
	// 	return (1);
	printf("Everything went well\n");
	return (0);
}
