/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/26 23:53:51 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "settings.h"

void	put_loading_screen(t_cub *data)
{
	int	text_width;
	int	text_pos_x;

	text_width = (sizeof(STARTING_TEXT) / sizeof(char) - 1) * 6;
	text_pos_x = (WINDOW_WIDTH / 2) - (text_width / 2);
	mlx_string_put(data->mlx_ptr, data->win_ptr,
		text_pos_x, WINDOW_HEIGHT / 2, 0xFFFFFFFF, STARTING_TEXT);
}

int	ft_mlx_initialize_pointers(t_cub *data)
{
	if (data->mlx_ptr == NULL)
		return (1);
	if (ft_mlx_create_window_and_image(data))
		return (1);
	put_loading_screen(data);
	return (0);
}

int	ft_mlx_create_window_and_image(t_cub *data)
{
	data->win_ptr = mlx_new_window(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (data->win_ptr == NULL)
	{
		return (1);
	}
	data->screen.mlx_img = mlx_new_image(data->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT);
	if (data->screen.mlx_img == NULL)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		return (1);
	}
	data->screen.addr = mlx_get_data_addr(data->screen.mlx_img,
			&data->screen.bpp, &data->screen.line_len, &data->screen.endian);
	data->screen.size = (t_point2i){{WINDOW_WIDTH, WINDOW_HEIGHT}};
	return (0);
}
