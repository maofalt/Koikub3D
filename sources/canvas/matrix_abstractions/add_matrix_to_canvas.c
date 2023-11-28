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

static int	apply_transformation_at_position(
	t_canvas *canvas,
	t_matrix3x3	transform_matrix,
	t_point2i	pos)
{
	t_matrix3x3	translation;
	t_matrix3x3	translation_back;

	translation = translation_matrix((t_point2d){{pos.x, pos.y}});
	if (apply_matrix_transformation(canvas, translation))
		return (1);
	if (apply_matrix_transformation(canvas, transform_matrix))
		return (1);
	translation_back = translation_matrix((t_point2d){{-pos.x, -pos.y}});
	if (apply_matrix_transformation(canvas, translation_back))
		return (1);
	return (0);
}

//apply zoom centered in  a given position 
int	apply_zoom_at_position(t_canvas *canvas, double zoom, t_point2i pos)
{
	t_matrix3x3	zoom_matrix;

	zoom_matrix = scaling_matrix((t_point2d){{zoom, zoom}});
	return (apply_transformation_at_position(canvas, zoom_matrix, pos));
}

int	apply_rotation_at_position(t_canvas *canvas, double angle, t_point2i pos)
{
	t_matrix3x3	rot_matrix;

	rot_matrix = rotation_matrix(angle);
	return (apply_transformation_at_position(canvas, rot_matrix, pos));
}
