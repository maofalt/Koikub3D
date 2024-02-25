/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_penguin_logic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 02:46:54 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 05:46:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dynamic_array.h"
#include "game_loop.h"
#include "maths_utils.h"
#include "matrix.h"
#include "settings.h"
#include "structures.h"

static void	normalize_vector_3d(t_vector4d *vec)
{
	double	reverse_lenght;
	double	lenght;

	lenght = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (lenght == 0)
		return ;
	reverse_lenght = 1 / lenght;
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

t_vector4d	_get_penguin_world_acceleration(
	t_entity *self,
	t_entity_penguin_data *self_data,
	t_game_data *game_data)
{
	t_vector4d	acceleration;


	if (self_data->have_target == 0)
	{
		return ((t_vector4d){{0, 0, 0, 0}});
	}


	acceleration.x = self_data->target.x - self->physics.pos.x;
	acceleration.y = self_data->target.y - self->physics.pos.y;
	acceleration.z = 0;
	// if (acceleration.x * acceleration.x + acceleration.y * acceleration.y < 10)
	// {
	// 	acceleration = (t_vector4d){{0, 0, 0, 0}};
	// 	return (acceleration);
	// }
	normalize_vector_3d(&acceleration);
	acceleration.vec *= DEFAULT_PLAYER_ACCELERATION / 2;//3;
	return (acceleration);
}

void	_update_penguin_direction(
	t_entity *self,
	t_entity_penguin_data *self_data,
	t_game_data *game_data)
{
	t_vector4d	direction;

	(void)self_data;
	direction.x = game_data->state.player->physics.pos.x - self->physics.pos.x;
	direction.y = game_data->state.player->physics.pos.y - self->physics.pos.y;
	direction.z = 0;
	normalize_vector_3d(&direction);
	self->physics.dir.x = direction.x * 0.1 + self->physics.dir.x * 0.90;
	self->physics.dir.y = direction.y * 0.1 + self->physics.dir.y * 0.90;
	self->physics.right = self->physics.dir;
	self->physics.right.x = self->physics.dir.y;
	self->physics.right.y = -self->physics.dir.x;
}

#include "raycaster.h"

int	get_current_dijkstra_node(
	t_entity *self,
	t_game_data *game_data)
{
	t_tree_node				*node;
	t_bsp_tree_node_data	*node_data;
	t_list					*segment_list;
	t_segment_d				*segment;

	node = bsp_search_point_fast(
			game_data->map_data.bsp,
			&self->physics.pos);
	node_data = node->data;
	return (node_data->sector_data.dijkstra_id);
	// segment_list = node_data->sector_segments;
	// while (segment_list)
	// {
	// 	segment = segment_list->content;
	// 	if (segment->data.type == PORTAL)
	// 	{
	// 		return (segment->data.data.portal.dijkstra_id);
	// 	}
	// 	segment_list = segment_list->next;
	// }
	return (-1);
}

void	display_dijkstra_path(t_dijkstra *dijkstra, int start, int end)
{
	int i;
	int j;

	j = 10;
	i = end;
	if (dijkstra->previous[i] == -1)
	{
		printf("Non-reachable node\n");
		return;
	}
	while (i != start && j-- > 0)
	{
		printf("node %d\n", i);
		i = dijkstra->previous[i];
	}
	printf("node %d\n", i);
}

void	print_djisrka(t_dijkstra *dijkstra)
{
	int i;
	int j;

	i = 0;
	while (i < dijkstra->graph_size)
	{
		// j = 0;
		// while (j < dijkstra->graph_size)
		// {
			printf("%d ", dijkstra->previous[i]);
			// j++;
		// }
		printf("\n");
		i++;
	}
}

//TODO clean and optimize that (use a id to segment map for example)
t_segment_d *get_portal_segment_from_id(
	t_entity *self,
	t_game_data *game_data, int id)
{
	t_tree_node				*node;
	t_bsp_tree_node_data	*node_data;
	t_list					*segment_list;
	t_segment_d				*segment;

	node = bsp_search_point_fast(
			game_data->map_data.bsp,
			&self->physics.pos);
	node_data = node->data;
	segment_list = node_data->sector_segments;
	while (segment_list)
	{
		segment = segment_list->content;
		if (segment->data.type == PORTAL
			&& segment->data.data.portal.dijkstra_id == id)
		{
			return (segment);
		}
		segment_list = segment_list->next;
	}
	return (NULL);
}


t_vector4d	get_segment_center(t_segment_d *segment)
{
	t_vector4d	center;

	center.x = (segment->point_a.x + segment->point_b.x) / 2;
	center.y = (segment->point_a.y + segment->point_b.y) / 2;
	center.z = (segment->point_a.z);
	return (center);
}


t_vector4d	get_target_from_id(
	t_entity *self,
	t_game_data *game_data, int id)
{
	t_tree_node				*node;
	t_bsp_tree_node_data	*node_data;
	t_list					*segment_list;
	t_segment_d				*segment;

	node = bsp_search_point_fast(
			game_data->map_data.bsp,
			&self->physics.pos);
	node_data = node->data;
	if (node_data->sector_data.dijkstra_id == id)
	{
		return (node_data->sector_data.center);
	}
	segment_list = node_data->sector_segments;
	while (segment_list)
	{
		segment = segment_list->content;
		if (segment->data.type == PORTAL
			&& segment->data.data.portal.dijkstra_id == id)
		{
			return (get_segment_center(segment));
		}
		segment_list = segment_list->next;
	}
	return (self->physics.pos);
}
#include <assert.h>

void	update_path(t_entity *self, t_game_data *game_data)
{
	t_entity_penguin_data	*data;
	int						current_node;
	int						player_node;

	data = self->data;
	current_node = get_current_dijkstra_node(self, game_data);
	player_node = get_current_dijkstra_node(game_data->state.player, game_data);

	printf("current_node %d\n", current_node);
	printf("player_node %d\n", player_node);
	if (current_node == -1 || player_node == -1)
		return ;
	if (current_node == player_node)
	{
		data->have_target = 1;
		data->target = game_data->state.player->physics.pos;
		return ;
	}
	// if (current_node != data->dijkstra.start_node
	// 	|| player_node != data->dijkstra.end_node)
	// {
		dijkstra(&data->dijkstra, current_node);
	// }
	display_dijkstra_path(&data->dijkstra, current_node, player_node);
	if (data->dijkstra.previous[player_node] == -1)
	{
		printf("Non-reachable node\n");
		data->have_target = 0;
		return;
	}
	data->have_target = 1;
	while (data->dijkstra.previous[player_node] != current_node)
	{
		player_node = data->dijkstra.previous[player_node];
	}

	data->target = get_target_from_id(self, game_data, player_node);
		// t_segment_d *segment = get_portal_segment_from_id(
		// 		self, game_data, player_node);

		// if (segment != NULL)
		// {
		// data->target = get_segment_center(
		// 		segment);
		// }
		// else
		// {
		// 	data->target =
		// }
}


void	entity_penguin_update_movements(t_entity *self, t_game_data *game_data)
{
	t_entity_penguin_data	*data;
	t_vector4d				world_space_acceleration;

	data = self->data;
	update_path(self, game_data);
	world_space_acceleration
		= _get_penguin_world_acceleration(self, data, game_data);
	_update_penguin_direction(self, data, game_data);
	self->physics.acceleration.vec = world_space_acceleration.vec;
	// print_djisrka(&data->dijkstra);
}
