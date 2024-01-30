/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:12:45 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 23:12:59 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "game_loop.h"

//TODO move this in .h
int	map_convert(t_cub *data, t_map_data *map_data);

int	game_init(t_cub *data, t_canvas *canvas)
{
	data->update = UPDATE;
	printf("game_init\n");
	if (map_convert(data, &data->game_data.map_data))
		return (free_everything(*data), 1);
	if (game_render_init(data, &data->game_data, canvas))
		return (free_everything(*data), 1);
	data->game_data.state.player = data->player;
	data->game_data.map_data.texture_manager = &data->texture_manager;
	game_precalculate_map(&data->game_data);
	return (0);
}
