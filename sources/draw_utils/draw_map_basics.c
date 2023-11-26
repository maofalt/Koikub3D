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

inline	void	put_pixel_on_virtual_canvas(t_canvas *canvas,
	t_point2i coord,
	t_color color)
{
	int	offset;

	if (coord.x >= 0 && coord.x < canvas->size.x && coord.y >= 0
		&& coord.y < canvas->size.y)
	{
		offset = coord.y * canvas->size.x + coord.x;
		canvas->pixels[offset] = color;
	}
}

static	void	initialize_bresenham(t_point2i *step,
	t_point2i *delta,
	t_point2i *start,
	t_point2i *end)
{
	delta->x = abs(end->x - start->x);
	delta->y = abs(end->y - start->y);
	step->x = -1;
	if (start->x < end->x)
		step->x = 1;
	step->y = -1;
	if (start->y < end->y)
		step->y = 1;
}

int	draw_line_on_map(t_canvas *canvas,
	t_point2i start,
	t_point2i end,
	t_color color)
{
	t_point2i		delta;
	int				err;
	int				e2;
	t_point2i		step;

	//printf(" \tnew s: [%d, %d]", start.x, start.y);
	//printf(" \tnew e: [%d, %d]\n", end.x, end.y);
	initialize_bresenham(&step, &delta, &start, &end);
	err = delta.x - delta.y;
	while (1)
	{
		put_pixel_on_virtual_canvas(canvas, start, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 > -delta.y)
		{
			err -= delta.y;
			start.x += step.x;
		}
		if (e2 < delta.x)
		{
			err += delta.x;
			start.y += step.y;
		}
	}	
	return (0);
}
