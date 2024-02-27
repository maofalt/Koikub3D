/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 01:12:45 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 19:20:03 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_engine.h"
#include "draw_utils.h"
#include "game_loop.h"
#include "settings.h"
#include "error.h"
#include "map_to_edges.h"
#include "bsp_builder.h"

void	tmp_set_segments_textures(t_list *lst, t_cub *data)
{
	t_segment_d	*seg;

	while (lst)
	{
		seg = lst->content;
		seg->data.data.wall.texture.texture = data->texture_manager.textures;
		seg->data.data.wall.texture.offset = 0;
		lst = lst->next;
	}
}

//TODO: Move this to a better place
int	map_convert(t_cub *data, t_map_data *map_data)
{
	t_list		**segments_lst;
	t_tree_node	*tree;

	tree = NULL;
	segments_lst = &data->segments_list;
	if (!*segments_lst && extract_edge_recursively(data->map, segments_lst))
		return (1);
	tmp_set_segments_textures(*segments_lst, data);
	if (construct_bsp(segments_lst, &tree))
	{
		ft_lstclear(segments_lst, free);
		return (1);
	}
	map_data->segments = *segments_lst;
	map_data->bsp = tree;
	return (0);
}

int	spawn_default_entities(t_game_data *game_data)
{
	t_spawn		spawn;
	t_entity	*entity;

	spawn = game_data->map_data.player_spawn;
	entity = entity_player_spawn(game_data, game_data->map_data.player_spawn);
	if (entity == NULL)
		return (1);
	game_data->state.player = entity;
	entity = entity_torch_spawn(game_data, game_data->map_data.player_spawn);
	if (entity == NULL)
		return (1);
	entity = entity_penguin_spawn(game_data, spawn);
	if (entity == NULL)
		return (1);
	return (0);
}

int	game_init(t_cub *data, t_canvas *canvas)
{
	data->update = UPDATE;
	if (map_convert(data, &data->game_data.map_data))
		return (fatal_error(data, "cannot convert map"));
	if (game_render_init(data, &data->game_data, canvas))
		return (fatal_error(data, "cannot init game render"));
	data->game_data.state.entities = sparse_array_init(sizeof(t_entity),
			DEFAULT_ENTITIES_ARRAY_SIZE);
	if (data->game_data.state.entities == NULL)
		return (fatal_error(data, "cannot init entities array"));
	data->game_data.map_data.texture_manager = &data->texture_manager;
	data->game_data.map_data.ceil_color.d = data->celling;
	data->game_data.map_data.floor_color.d = data->floor;
	data->game_data.inputs = &data->inputs;
	data->game_data.map_data.player_spawn.dir = data->player.dir;
	data->game_data.map_data.player_spawn.pos = data->player.pos;
	data->game_data.map_data.player_spawn.pos.z = 1;
	data->game_data.state.delta_time = 0;
	data->game_data.state.time_since_start = 0;
	game_precalculate_map(&data->game_data);
	if (spawn_default_entities(&data->game_data))
		return (fatal_error(data, "cannot spawn entities"));
	data->game_data.state.is_ready = true;
	return (0);
}
