/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_canvas_operation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/15 01:26:03 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"


void	canvas_to_mlx_image(t_cub *data)
{
	const t_canvas	*final_canvas
		= get_canvas_from_list(data->canvas_list, MAP);
	int				x;
	int				y;
	int				canvas_index;
	int				color;

	if (!data->screen.mlx_img || !data->screen.addr)
		return ;

	y = 0;
	while (y < final_canvas->size.y)
	{
		x = 0;
		while (x < final_canvas->size.x)
		{
			canvas_index = y * final_canvas->size.x + x;
			color = (int)final_canvas->pixels[canvas_index].rgb_color;
			img_pix_put(&(data->screen), x, y, color);
			x++;
		}
		y++;
	}
}

