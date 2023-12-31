/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2023/11/23 14:02:17 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"

int	ft_mlx_initialize_pointers(t_cub *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (data->win_ptr == NULL)
	{
		free(data->mlx_ptr);
		return (1);
	}
	if (ft_mlx_create_window_and_image(data))
		return (1);
	return (0);
}

int	ft_mlx_create_window_and_image(t_cub *data)
{
	(void)data;
	data->screen.mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->screen.mlx_img == NULL)
	{
		free(data->mlx_ptr);
		free(data->win_ptr);
		return (1);
	}
	data->screen.addr = mlx_get_data_addr(data->screen.mlx_img,
			&data->screen.bpp, &data->screen.line_len, &data->screen.endian);
	data->screen.size = (t_point2i){{WINDOW_WIDTH, WINDOW_HEIGHT}};
	return (0);
}
