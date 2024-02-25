/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra_from_bsp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:47:45 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 03:12:09 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"
#include "structures.h"

static void	_compute_segment(t_game_data *game_data, t_segment_d *segment,
		t_bsp_tree_node_data *sector, t_dijkstra *dijkstra)
{
	int		portal_id;

	(void)game_data;
	if (segment->data.type == PORTAL)
	{
		portal_id = segment->data.data.portal.dijkstra_id;

		t_segment_d	*other_segment;
		t_tree_node	*other_sector;
		int			other_sector_id;
		other_segment = segment->data.data.portal.destination;

		other_sector = other_segment->data.data.portal.tree_node_ptr;
		other_sector_id = ((t_bsp_tree_node_data *)other_sector->data)
			->sector_data.dijkstra_id;

		dijkstra->graph[portal_id * dijkstra->graph_size + other_sector_id] = 1;


		//connect with other portals of sector
		// t_list		*seg_lst;
		// int		other_portal_id;

		// seg_lst = sector->sector_segments;
		// while (seg_lst)
		// {
		// 	other_segment = seg_lst->content;
		// 	if (other_segment->data.type == PORTAL)
		// 	{
		// 		other_portal_id = other_segment->data.data.portal.dijkstra_id;
		// 		if (other_portal_id != portal_id)
		// 			dijkstra->graph[portal_id * dijkstra->graph_size + other_portal_id] = 1;
		// 	}
		// 	seg_lst = seg_lst->next;
		// }
	}
}


static void	_compute_sector(t_game_data *game_data, t_bsp_tree_node_data *sector,
		t_dijkstra *dijkstra)
{

	t_list		*seg_lst;
	t_segment_d	*other_segment;
	int		other_portal_id;
	int		portal_id;

	seg_lst = sector->sector_segments;
	portal_id = sector->sector_data.dijkstra_id;
	while (seg_lst)
	{
		other_segment = seg_lst->content;
		if (other_segment->data.type == PORTAL)
		{
			other_portal_id = other_segment->data.data.portal.dijkstra_id;
			if (other_portal_id != portal_id)
				dijkstra->graph[portal_id * dijkstra->graph_size + other_portal_id] = 1;
		}
		seg_lst = seg_lst->next;
	}
}

static void	_iterate_sector_segments(t_game_data *game_data, t_tree_node *node
		,t_dijkstra *dijkstra)
{
	t_list		*seg_lst;
	t_segment_d	*segment;

	_compute_sector(game_data, node->data, dijkstra);
	seg_lst = ((t_bsp_tree_node_data *)node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		_compute_segment(game_data, segment, node->data, dijkstra);
		seg_lst = seg_lst->next;
	}
}

static void	_iterate_bsp_tree(t_game_data *game_data, t_tree_node *node,
	t_dijkstra *dijkstra
)
{
	if (node == NULL)
		return ;
	if (node->left == NULL && node->right == NULL)
	{
		_iterate_sector_segments(game_data, node, dijkstra);
		return ;
	}
	_iterate_bsp_tree(game_data, node->left, dijkstra);
	_iterate_bsp_tree(game_data, node->right, dijkstra);
}

void	dijkstra_from_bsp(t_game_data *game_data, t_dijkstra *dijkstra)
{
	_iterate_bsp_tree(game_data, game_data->map_data.bsp, dijkstra);
	printf("portal count: %d\n", game_data->map_data.portal_count);
}
