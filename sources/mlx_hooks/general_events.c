/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_events.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 21:35:41 by motero            #+#    #+#             */
/*   Updated: 2024/02/27 19:21:53 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"

int	ft_destroy_window(t_cub *data)
{
	mlx_loop_end(data->mlx_ptr);
	return (0);
}

int	ft_handle_game_keyrelease(
	int keysym,
	void *canvas,
	t_cub *data)
{
	(void)canvas;
	ft_movements_keys(keysym, data, 0);
	return (0);
}

int	ft_handle_game_keypress(
	int keysym,
	void *canvas,
	t_cub *data)
{
	(void)canvas;
	ft_destroy_window_button(keysym, data);
	ft_movements_keys(keysym, data, 1);
	data->update = 1;
	return (0);
}
