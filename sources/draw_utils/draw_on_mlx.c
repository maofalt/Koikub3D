/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_on_mlx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/03 21:34:47 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	canvas_to_mlx_image(t_img_data screen, t_canvas *final_canvas)
{
	if (!screen.mlx_img || !screen.addr || screen.bpp != 32)
		return ;
	ft_memcpy(screen.addr, final_canvas->pixels,
		final_canvas->size.x * final_canvas->size.y * 4);
}
