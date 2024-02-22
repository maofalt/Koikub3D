/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_canvas_operation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 19:53:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	start_drawing(t_canvas *canvas, t_point2i start_point)
{
	t_map_editor_data	*map_editor;
	t_point2i			start_point_canvas;

	map_editor = &canvas->data.map_editor;
	start_point_canvas = screen_to_canvas(start_point, canvas);
	map_editor->last_point = apply_transformations_to_point(start_point_canvas,
			map_editor->matrix_operations);
}

void	update_drawing(t_canvas *canvas, t_point2i current_point, t_color color)
{
	t_map_editor_data	*map_editor;
	t_point2i			current_point_canvas;
	t_point2i			last_point_canvas;

	map_editor = &canvas->data.map_editor;
	current_point_canvas = screen_to_canvas(current_point, canvas);
	last_point_canvas = back_transform_point_by_matrix(
			point2d_to_vector4d(&(map_editor->last_point)),
			get_inverse_transformation_matrix(
				map_editor->transformation_matrix));
	draw_line_on_map(canvas, last_point_canvas, current_point_canvas, color);
}

//check for erros here at the end after new _segment
void	end_drawing(t_canvas *canvas, t_point2i end_point, t_color color)
{
	t_point2i			current_point_canvas;
	t_segment_d			segment;
	t_point2d			start;
	t_point2d			end;
	t_map_editor_data	*map_editor;

	(void)color;
	map_editor = &canvas->data.map_editor;
	current_point_canvas = screen_to_canvas(end_point, canvas);
	start = map_editor->last_point;
	end = apply_transformations_to_point(current_point_canvas,
			map_editor->matrix_operations);
	ft_memset(&segment, 0, sizeof(t_segment_d));
	if (start.x == end.x && start.y == end.y)
		return ;
	segment.point_a = point2d_to_vector4d(&start);
	segment.point_b = point2d_to_vector4d(&end);
	add_segment_to_lst(&map_editor->segments, segment);
}
