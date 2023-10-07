/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/07 19:47:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	draw_segment(
			t_img_data *img,
			t_segment_d const *const segment,
			int color
			)
{
	t_point2d	delta;
	t_point2d	cursor;
	double		step;

	delta.vec = segment->point_b.vec - segment->point_a.vec;
	if (fabs(delta.x) >= fabs(delta.y))
		step = fabs(delta.x);
	else
		step = fabs(delta.y);
	delta.vec = delta.vec / step;
	cursor.vec = segment->point_a.vec;
	while (step > 0)
	{
		img_pix_put(img, cursor.x, cursor.y, color);
		cursor.x = cursor.x + delta.x;
		cursor.y = cursor.y + delta.y;
		step--;
	}
}
