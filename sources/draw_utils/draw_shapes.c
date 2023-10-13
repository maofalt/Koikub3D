/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/13 21:54:13 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

void	draw_rectangle(t_img_data *img, t_vector_i pos, t_vector_i size, int color)
{
	int	x;
	int	y;

	y = pos[1];
	while (y < pos[1] + size[1])
	{
		x = pos[0];
		while (x < pos[0] + size[0])
		{
			img_pix_put(img, x, y, color);
			x++;
		}
		y++;
	}
}
