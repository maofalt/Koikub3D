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
	t_point2i	start_point_canvas;

	printf("start drawing\n");
	start_point_canvas = screen_to_canvas(start_point, canvas);
	canvas->last_point = apply_transformations_to_point(start_point_canvas,
			canvas->matrix_operations);
}

void	update_drawing(t_canvas *canvas, t_point2i current_point, t_color color)
{
	t_point2i	current_point_canvas;
	t_point2i	last_point_canvas;

	printf("update drawing\n");
	current_point_canvas = screen_to_canvas(current_point, canvas);
	last_point_canvas = back_transform_point_by_matrix(
			point2d_to_vector4d(&(canvas->last_point)),
			get_inverse_transformation_matrix(canvas->transformation_matrix));
	draw_line_on_map(canvas, last_point_canvas, current_point_canvas, color);
}

//check for erros here at the end after new _segment
void	end_drawing(t_canvas *canvas, t_point2i end_point, t_color color)
{
	t_point2i	current_point_canvas;
	t_point2i	last_point_canvas;
	t_segment_d	segment;
	t_point2d	start;
	t_point2d	end;

	printf("end drawing\n");
	current_point_canvas = screen_to_canvas(end_point, canvas);
	printf("\t transforming last point canvas\n");
	last_point_canvas = back_transform_point_by_matrix(
			point2d_to_vector4d(&(canvas->last_point)),
			get_inverse_transformation_matrix(canvas->transformation_matrix));
	printf("\t drawing line on map\n");
	draw_line_on_map(canvas, last_point_canvas, end_point, color);
	start = canvas->last_point;
	printf("\t transforming current point canvas for segment\n");
	end = apply_transformations_to_point(current_point_canvas,
			canvas->matrix_operations);

	ft_memset(&segment, 0, sizeof(t_segment_d));
	segment.point_a = point2d_to_vector4d(&start);
	segment.point_b = point2d_to_vector4d(&end);	
	add_segment_to_lst(&canvas->segments, segment);

// Recalculate the segment's point_a and point_b pixel coordinates
    t_point2i recalculated_pixel_point_a = back_transform_point_by_matrix(
        segment.point_a, 
        get_inverse_transformation_matrix(canvas->transformation_matrix)
    );

    t_point2i recalculated_pixel_point_b = back_transform_point_by_matrix(
        segment.point_b, 
        get_inverse_transformation_matrix(canvas->transformation_matrix)
    );

    // Printing recalculated pixel points for debugging
	printf("New transformign back to pixel points\n");
    printf("Recalculated Pixel Point A: x: %d, y: %d\n", recalculated_pixel_point_a.x, recalculated_pixel_point_a.y);
    printf("Recalculated Pixel Point B: x: %d, y: %d\n", recalculated_pixel_point_b.x, recalculated_pixel_point_b.y);
	printf("original pixel points\n");
	printf("Pixel Point A: x: %d, y: %d\n", current_point_canvas.x, current_point_canvas.y);
	printf("Pixel Point B: x: %d, y: %d\n", last_point_canvas.x, last_point_canvas.y);
}
