/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_canvas_operation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 22:10:14 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	start_drawing(t_canvas *canvas, t_point2i start_point)
{
	canvas->last_point = screen_to_canvas(start_point, canvas);
}

void	update_drawing(t_canvas *canvas, t_point2i current_point, t_color color)
{
	t_point2i	current_point_canvas;

	current_point_canvas = screen_to_canvas(current_point, canvas);
	draw_line_on_map(canvas, canvas->last_point, current_point_canvas, color);
}

void	end_drawing(t_canvas *canvas, t_point2i end_point, t_color color)
{
	t_point2i	current_point_canvas;
	t_segment_d	segment;
	t_point2d	start;
	t_point2d	end;

	current_point_canvas = screen_to_canvas(end_point, canvas);
	draw_line_on_map(canvas, canvas->last_point, end_point, color);
	start = apply_transformations_to_point(canvas->last_point,
			canvas->matrix_operations);
	end = apply_transformations_to_point(current_point_canvas,
			canvas->matrix_operations);
	//canvas->transformation_matrix = identity_matrix();
	ft_memset(&segment, 0, sizeof(t_segment_d));
	segment.point_a = point2d_to_vector4d(&start);
	segment.point_b = point2d_to_vector4d(&end);
	//check for erros here!!
	add_segment_to_lst(&canvas->segments, segment);
}
