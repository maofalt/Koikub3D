/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d_flush.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 11:36:26 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/15 11:36:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "draw_utils.h"

#include "render_3D.h"

static inline void	render_put_scaled_pixel_to_canvas(t_3d_render *render, int x, int y, t_color color)
{
	t_color *const pixels = render->canvas->pixels;
	int i = 0;
	int j = 0;

	while (i < render->scale_factor_y)
	{
		j = 0;
		while (j < render->scale_factor_x)
		{
			pixels[(y * render->scale_factor_y + i) * render->canvas->size.x + (x * render->scale_factor_x + j)] = color;
			j++;
		}
		++i;
	}
}

void	render_3d_flush_to_canvas(t_3d_render *render)
{
	int y = 0;
	int x = 0;

	while (y < render->height)
	{
		x = 0;
		while (x < render->width)
		{
			render_put_scaled_pixel_to_canvas(render,
				x,
				y,
				render->buffers.color[y * render->width + x]);
			++x;
		}
		++y;
	}
}
