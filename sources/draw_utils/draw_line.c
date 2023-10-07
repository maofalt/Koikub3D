/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/07 12:53:19 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	draw_segment(t_img_data *img, t_segment_i segment, int color)
{
	t_point2d	delta;
	t_point2d	cursor;
	double		step;
	t_point2d	point_a;
	t_point2d	point_b;

	point_a.vec = (t_v2d){(double)segment.point_a.x, (double)segment.point_a.y};
	point_b.vec = (t_v2d){(double)segment.point_b.x, (double)segment.point_b.y};
	delta.vec = point_b.vec - point_a.vec;
	if (fabs(delta.x) >= fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.vec = delta.vec / step;
	cursor.vec = point_a.vec;
	while (step > 0)
	{
		img_pix_put(img, cursor.x, cursor.y, color);
		cursor.x = cursor.x + delta.x;
		cursor.y = cursor.y + delta.y;
		step--;
	}
}
