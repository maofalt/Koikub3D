/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 05:47:29 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 19:39:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"
#include "maths_utils.h"

void	game_update(t_game_data *game_data)
{
	game_data->state.delta_time = 1;
	game_data->state.time_since_start += 1;
	entities_destroy_marked(game_data);
	entities_update(game_data);
	game_update_camera(game_data);
	sector_edit_height_handle_event(game_data);
}

int	game_loop(void *self, t_cub *data)
{
	(void)self;
	if (data->win_ptr == NULL || !data->game_data.state.is_ready)
		return (1);
	game_update(&data->game_data);
	game_render(data);
	count_fps();
	data->update = UPDATE;
	return (0);
}
