/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_member_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 00:24:41 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

int	render_base(void *self, t_cub *data)
{
	t_canvas	*canvas;

	(void)data;
	canvas = (t_canvas *)self;
	if (canvas && canvas->event_handlers.render)
		return (canvas->event_handlers.render(self, data));
	return (-1);
}

void	fill_canvas_with_image(t_canvas *canvas, t_img_data *img)
{
	t_point2i	pos;
	t_point2i	img_pos;
	t_point2d	scale;
	t_color		*pixel;

	scale.x = (double)img->size.x / canvas->size.x;
	scale.y = (double)img->size.y / canvas->size.y;
	pos.y = 0;
	while (pos.y < canvas->size.y)
	{
		pos.x = 0;
		while (pos.x < canvas->size.x)
		{
			img_pos.x = (int)(pos.x * scale.x);
			img_pos.y = (int)(pos.y * scale.y);
			pixel = (t_color *)(img->addr
					+ (img_pos.y * img->line_len + img_pos.x * (img->bpp / 8)));
			canvas->pixels[pos.y * canvas->size.x + pos.x] = *pixel;
			pos.x++;
		}
		pos.y++;
	}
}
