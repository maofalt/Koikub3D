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
		t_point2d coord,
		t_color color)
{
	(void)canvas;
	(void)coord;
	(void)color;
}

// Bresenham's line drawing algorithm
int	draw_line_on_map(t_canvas *canvas,
	t_point2d start,
	t_point2d end,
	t_color color)
{
	(void)canvas;
	(void)start;
	(void)end;
	(void)color;
	return (0);
}

void	start_drawing(t_canvas *canvas, t_point2i start_point)
{
	canvas->last_point = start_point;
}

void	update_drawing(t_canvas *canvas, t_point2i current_point, t_color color)
{
	draw_line_on_map(canvas, canvas->last_point, current_point, color);
	//canvas->last_point = current_point;
}

void	end_drawing(t_canvas *canvas, t_point2i end_point, t_color color)
{
	draw_line_on_map(canvas, canvas->last_point, end_point, color);
}
