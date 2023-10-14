/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_canvas_operation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/15 01:26:03 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

// A helper function to draw a pixel on the canvas.
void	put_pixel_on_canvas(t_canvas *canvas, t_point2d coord, t_color color)
{
	if (x >= 0 && x < canvas->size.x && y >= 0 && y < canvas->size.y)
	{
		canvas->pixels[y * canvas->size.x + x] = color;
	}
}

void	put_pixel_on_virtual_canvas(t_canvas *canvas, t_point2d coord, t_color color)
{
	t_point2d	start;
	t_point2d	end;
	t_point2d	virt;

	start = coord->start * canvas->pixel_scale;
	end = coord->end + canvas->pixel_scale;
	virt.y = start.y;
	while (virt_y < end_y)
	{
		virt_x = start_x;
		while (virt.x < end.x)
		{
			if (virt.x >= 0 && virt.x < canvas->size.x
				&& virt.y >= 0 && virt.y < canvas->size.y)
			{
				canvas->pixels[(int)virt..y * canvas->size.x
					+ (int)virt.x] = color;
			}
			virt.x++;
		}
		virt.y++;
	}
}

// Bresenham's line drawing algorithm
int	draw_line_on_map(t_canvas *canvas,
	t_point2d start,
	t_point2d end,
	t_color color)
{
	const t_point2d	delta = (t_point2d){abs((end.x - start.x) * canvas->pixel_scale),
		};
	const t_point2d	sign;
	double	dx = ;
	double	sx = start.x < end.x ? 1.0 / canvas->pixel_scale : -1.0 / canvas->pixel_scale;
	double	dy = -abs((end.y - start.y) * canvas->pixel_scale);
	double	sy = start.y < end.y ? 1.0 / canvas->pixel_scale : -1.0 / canvas->pixel_scale;
	double	err = dx + dy, e2;

	while (1)
	{
		put_pixel_on_virtual_canvas(canvas, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start.y += sy;
		}
	}
	return (0);
}

static t_point2d g_last_point; // to keep track of the last point during drawing

void start_drawing(t_canvas *canvas, t_point2d start_point) {
	g_last_point = start_point;
}

void update_drawing(t_canvas *canvas, t_point2d current_point, t_color color) {
	draw_line_on_map(canvas, g_last_point, current_point, color);
	g_last_point = current_point;
}

void end_drawing(t_canvas *canvas, t_point2d end_point, t_color color) {
	draw_line_on_map(canvas, g_last_point, end_point, color);
}
