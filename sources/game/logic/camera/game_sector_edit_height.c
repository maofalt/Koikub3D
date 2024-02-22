/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sector_edit_height.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 19:32:52 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 19:35:47 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"
#include "maths_utils.h"
#include "render_3D.h"

void	update_player_sector_ceil(t_3d_render *render, double value)
{
	t_tree_node				*node;
	t_list					*seg_lst;
	t_segment_d				*segment;

	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));
	((t_bsp_tree_node_data *)(node->data))->sector_data.ceil -= value;
	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		segment->data.ceil -= value;
		seg_lst = seg_lst->next;
	}
}

void	update_player_sector_floor(t_3d_render *render, double value)
{
	t_tree_node				*node;
	t_list					*seg_lst;
	t_segment_d				*segment;

	node = bsp_search_point(render->map->bsp,
			vector4d_to_point2d(&render->camera->pos));
	((t_bsp_tree_node_data *)(node->data))->sector_data.floor += value;
	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		segment->data.floor += value;
		seg_lst = seg_lst->next;
	}
}

void	sector_edit_height_handle_event(t_game_data *game_data)
{
	if (game_data->inputs->action_states[a_decrease_sector_ceil])
	{
		printf("decrease \n");
		update_player_sector_ceil(&game_data->game_view_render, -1);
	}
	if (game_data->inputs->action_states[a_increase_sector_ceil])
	{
		update_player_sector_ceil(&game_data->game_view_render, 1);
		printf("increase \n");
	}
	if (game_data->inputs->action_states[a_decrease_sector_floor])
	{
		printf("decrease \n");
		update_player_sector_floor(&game_data->game_view_render, -1);
	}
	if (game_data->inputs->action_states[a_increase_sector_floor])
	{
		update_player_sector_floor(&game_data->game_view_render, 1);
		printf("increase \n");
	}
}
