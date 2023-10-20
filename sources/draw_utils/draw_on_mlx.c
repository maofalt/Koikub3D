/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/17 06:03:29 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

// 	0000 0000   0000 0000   0000 0000   0000 0000

// void		canvas_to_mlx_image(t_img_data screen, t_canvas *final_canvas)
// {
// 	int					color;
// 	char				*pixel;
// 	t_color				*canvas_pixel;
// 	const t_point2i		size = (t_point2i){{final_canvas->size.x,
// 		final_canvas->size.y}};
// 	const int			total_pixels = size.y * size.x;
// 	const int			pixel_offset = screen.bpp >> 3;

// 	if (!screen.mlx_img || !screen.addr)
// 		return ;
// 	canvas_pixel = final_canvas->pixels;
// 	for (int i = 0; i < total_pixels; i++, canvas_pixel++)
// 	{
// 		pixel = screen.addr + (i / size.x) * screen.line_len
// 			+ (i % size.x) * pixel_offset;
// 		color = (int)canvas_pixel->rgb_color;
// 		*(int *)pixel = color;
// 	}
// }

void	canvas_to_mlx_image(t_img_data screen, t_canvas *final_canvas)
{
	if (!screen.mlx_img || !screen.addr || screen.bpp != 32)
		return ;
	ft_memcpy(screen.addr, final_canvas->pixels,
		final_canvas->size.x * final_canvas->size.y * 4);
}
