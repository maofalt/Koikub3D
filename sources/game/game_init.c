/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:12:45 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 07:08:11 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "game_loop.h"
#include "settings.h"


void	spawn_default_entities(t_game_data *game_data)

{
	t_entity	*entity;

	entity = entity_player_spawn(game_data, game_data->map_data.player_spawn);
	if (entity == NULL)
		return ;
	game_data->state.player = entity->data;
	entity = entity_torch_spawn(game_data, game_data->map_data.player_spawn);
	if (entity == NULL)
		return ;

	entity = entity_monster_spawn(game_data, game_data->map_data.player_spawn);
	if (entity == NULL)
		return ;


}


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
	data->game_data.state.entities = sparse_array_init(sizeof(t_entity),
			DEFAULT_ENTITIES_ARRAY_SIZE);
	if (data->game_data.state.entities == NULL)
	{
		return (free_everything(*data), 1);
	}
	data->game_data.map_data.texture_manager = &data->texture_manager;
	data->game_data.map_data.ceil_color.d = data->celling;
	data->game_data.map_data.floor_color.d = data->floor;
	data->game_data.inputs = &data->inputs;
	data->game_data.map_data.player_spawn.dir = data->player.dir;
	data->game_data.map_data.player_spawn.pos = data->player.pos;
	data->game_data.map_data.player_spawn.pos.z = 1;
	data->game_data.delta_time = 1;
	game_precalculate_map(&data->game_data);
	spawn_default_entities(&data->game_data);
	return (0);
}
