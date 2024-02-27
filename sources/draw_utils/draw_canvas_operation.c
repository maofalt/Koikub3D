/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_canvas_operation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 19:19:51 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

static inline	void	put_pixel_on_virtual_canvas(t_canvas *canvas,
	t_point2d coord,
	t_color color)
{
	int	offset;

	if (coord.x >= 0 && coord.x < canvas->size.x && coord.y >= 0
		&& coord.y < canvas->size.y)
	{
		offset = ((int)coord.y) * canvas->size.x + coord.x;
		canvas->pixels[offset] = color;
	}
}

void	draw_segment_canvas(
			t_canvas *canvas,
			t_segment_d const *const segment,
			t_color color
			)
{
	t_vector4d	delta;
	t_point2d	cursor;
	double		step;

	delta.vec = segment->point_b.vec - segment->point_a.vec;
	if (fabs(delta.x) >= fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.vec = delta.vec / step;
	cursor.x = segment->point_a.x;
	cursor.y = segment->point_a.y;
	while (step > 0)
	{
		put_pixel_on_virtual_canvas(canvas, cursor, color);
		cursor.x = cursor.x + delta.x;
		cursor.y = cursor.y + delta.y;
		step--;
	}
}

void	fill_canvas(
			t_canvas *canvas,
			t_color color
			)
{
	t_color				*px;
	unsigned long long	image_size;

	if (color.d == 0)
	{
		ft_memset(canvas->pixels, 0,
			canvas->size.x * canvas->size.y * sizeof(t_color));
		return ;
	}
	px = canvas->pixels;
	image_size = canvas->size.y * canvas->size.x;
	while (image_size > 0)
	{
		*px = color;
		px ++;
		image_size --;
	}
}
