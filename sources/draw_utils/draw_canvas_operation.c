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
void	put_pixel_on_canvas(t_canvas *canvas, t_point2i coord, t_color color)
{
	if (coord.x >= 0 && coord.x < canvas->size.x
		&& coord.y >= 0 && coord.y < canvas->size.y)
	{
		canvas->pixels[coord.y * canvas->size.x + coord.x] = color;
	}
}

void	put_pixel_on_virtual_canvas(t_canvas *canvas,
		t_point2d coord,
		t_color color)
{
	t_point2d	start;
	t_point2d	end;
	t_point2d	virt;

	start = (t_point2d)(coord.vec * canvas->pixel_scale);
	end = (t_point2d)(coord.vec + canvas->pixel_scale);
	virt.y = start.y;
	while (virt.y < end.y)
	{
		virt.x = start.x;
		while (virt.x < end.x)
		{
			if (virt.x >= 0 && virt.x < canvas->size.x
				&& virt.y >= 0 && virt.y < canvas->size.y)
			{
				canvas->pixels[(int)virt.y * canvas->size.x
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
	const t_point2d	delta
		= (t_point2d){{fabs((end.x - start.x) * canvas->pixel_scale),
		-fabs((end.y - start.y) * canvas->pixel_scale)}};
	t_point2d		sign;
	double			err;
	double			e2;

	sign.x = 1.0 / canvas->pixel_scale;
	if (start.x > end.x)
		sign.x *= -1.0;
	sign.y = 1.0 / canvas->pixel_scale;
	if (start.y > end.y)
		sign.y *= -1.0;
	err = delta.x + delta.y;
	while (1)
	{
		put_pixel_on_virtual_canvas(canvas, start, color);
		printf("In loop: start(%f, %f), end(%f, %f)\n", start.x, start.y, end.x, end.y);
		if (start.x == end.x && start.y == end.y) {
			printf("Breaking out of loop.\n");
			break ;
		}
		e2 = 2 * err;
		if (e2 >= delta.y)
		{
			err += delta.y;
			start.x += sign.x;
		}
		if (e2 <= delta.x)
		{
			err += delta.x;
			start.y += sign.y;
		}
	}
	return (0);
}

void	start_drawing(t_canvas *canvas, t_point2d start_point)
{
	canvas->last_point = start_point;
}

void	update_drawing(t_canvas *canvas, t_point2d current_point, t_color color)
{
	draw_line_on_map(canvas, canvas->last_point, current_point, color);
	canvas->last_point = current_point;
}

void end_drawing(t_canvas *canvas, t_point2d end_point, t_color color)
{
	draw_line_on_map(canvas, canvas->last_point, end_point, color);
}
