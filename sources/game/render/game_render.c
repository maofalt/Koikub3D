/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 00:44:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 05:49:55 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "map_to_edges.h"
#include "bsp_builder.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include "game_loop.h"
#include <assert.h>

void	game_render(t_cub *data)
{
	texture_manager_update(&data->texture_manager);
	render_3d_draw(&data->game_data.game_view_render);
	entities_draw(&data->game_data);
	game_post_process_frame(&data->game_data.game_view_render);
	render_3d_flush_to_canvas(&data->game_data.game_view_render);
}

int	game_render_init(__attribute_maybe_unused__ t_cub *data,
	t_game_data *game_data,
	t_canvas *canvas)
{
	if (canvas == NULL)
		return (1);
	return (render_3d_init(&game_data->game_view_render, canvas,
			&game_data->state.player_camera, &game_data->map_data));
}

void	game_render_destroy(t_game_data *game_data)
{
	render_3d_destroy(&game_data->game_view_render);
}
