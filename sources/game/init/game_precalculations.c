/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_precalculations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:47:45 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/29 21:51:37 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"
#include "structures.h"

static void	_compute_segment(t_game_data *game_data, t_segment_d *segment,
		t_bsp_tree_node_data *sector)
{
	compute_segment_orientation(game_data, segment, sector);
	compute_segment_size(game_data, segment);
	compute_segment_normal(game_data, segment);
}

static void	_iterate_sector_segments(t_game_data *game_data, t_tree_node *node)
{
	t_list		*seg_lst;
	t_segment_d	*segment;

	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		_compute_segment(game_data, segment, node->data);
		seg_lst = seg_lst->next;
	}
}

static void	_iterate_bsp_tree(t_game_data *game_data, t_tree_node *node)
{
	if (node == NULL)
		return ;
	if (node->left == NULL && node->right == NULL)
	{
		_iterate_sector_segments(game_data, node);
		return ;
	}
	_iterate_bsp_tree(game_data, node->left);
	_iterate_bsp_tree(game_data, node->right);
}

void	game_precalculate_map(t_game_data *game_data)
{
	_iterate_bsp_tree(game_data, game_data->map_data.bsp);
}
