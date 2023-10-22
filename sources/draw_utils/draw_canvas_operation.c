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

void	put_pixel_on_virtual_canvas(t_canvas *canvas,
	t_point2i coord,
	t_color color)
{
	int	offset;

	if (coord.x >= 0 && coord.x < canvas->size.y && coord.y >= 0
		&& coord.y < canvas->size.x)
	{
		offset = coord.y * canvas->size.y + coord.x;
		canvas->pixels[offset] = color;
	}
}

int	draw_line_on_map(t_canvas *canvas,
	t_point2i start,
	t_point2i end,
	t_color color)
{
	const int	dx = abs(end.x - start.x);
	const int	dy = abs(end.y - start.y);
	int			err = dx - dy;
	int			sx = start.x < end.x ? 1 : -1;
	int			sy = start.y < end.y ? 1 : -1;

	while (1)
	{
		put_pixel_on_virtual_canvas(canvas, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			start.x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			start.y += sy;
		}
	}	
	return (0);
}

void	start_drawing(t_canvas *canvas, t_point2i start_point)
{
	canvas->last_point = screen_to_canvas(start_point, canvas);
}

void	update_drawing(t_canvas *canvas, t_point2i current_point, t_color color)
{
	t_point2i	current_point_canvas;

	current_point_canvas = screen_to_canvas(current_point, canvas);
	draw_line_on_map(canvas, canvas->last_point, current_point_canvas, color);
	//canvas->last_point = current_point;
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
	canvas->transformation_matrix = identity_matrix();
	ft_memset(&segment, 0, sizeof(t_segment_d));
	segment.point_a = point2d_to_vector4d(&start);
	segment.point_b = point2d_to_vector4d(&end);
	//check for erros here!!
	add_segment_to_lst(&canvas->segments, segment);
}
