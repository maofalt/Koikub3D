/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_display.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:07:02 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/06 18:08:49 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_render(t_cub *data)
{
	const t_segment_d	segment = {{{0.0, 0.0}}, {{1000.0, 200.0}}};

	printf("%f\n", data->player.pos[0]);
	rectangle(&data->screen, (t_vector_i){10, 10},
		(t_vector_i){100, 100}, 0xFFFFFFFF);
	draw_segment(&data->screen, segment, 0xFFFFFFFF);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
		data->screen.mlx_img, 0, 0);
	usleep(10000);
	return (0);
}
