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

void	canvas_to_mlx_image(t_img_data screen, t_canvas *final_canvas)
{
	if (!screen.mlx_img || !screen.addr || screen.bpp != 32)
		return ;
	printf("final cnavas address : %p\n", final_canvas);
	printf("final_canvas->size.x: %d, final_canvas->size.y: %d\n",
		final_canvas->size.x, final_canvas->size.y);
	ft_memcpy(screen.addr, final_canvas->pixels,
		final_canvas->size.x * final_canvas->size.y * 4);
}
