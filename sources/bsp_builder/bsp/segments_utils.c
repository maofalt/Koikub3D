/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:21:52 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/25 05:14:23 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"bsp_builder.h"

void	compute_bsp_segments_intersections(
		t_list *bsp_segments,
		t_segment_d *separator
		)
{
	t_bsp_segment	*segment;

	while (bsp_segments != NULL)
	{
		segment = bsp_segments->content;
		bsp_segment_compute_intersec(segment, separator);
		bsp_segments = bsp_segments->next;
	}
}

static void	lst_convert_and_free_bsp_segments(t_list **bsp_list)
{
	t_list			*current;
	t_bsp_segment	*bsp_seg;

	current = *bsp_list;
	while (current != NULL)
	{
		bsp_seg = (t_bsp_segment *)current->content;
		current->content = bsp_seg->segment;
		free(bsp_seg);
		current = current->next;
	}
}

void	tree_convert_bsp_segment_to_segments(t_tree_node *tree)
{
	if (tree == NULL)
		return ;
	if (tree->left == NULL && tree->right == NULL)
	{
		lst_convert_and_free_bsp_segments(
			&((t_bsp_tree_node_data*)tree->data)->sector_segments);
		return ;
	}
	tree_convert_bsp_segment_to_segments(tree->left);
	tree_convert_bsp_segment_to_segments(tree->right);
}

static void	lst_update_portals_links_to_segments(
	t_list **bsp_list,
	t_tree_node	*tree_node
	)
{
	t_list			*current;
	t_bsp_segment	*bsp_seg;

	current = *bsp_list;
	while (current != NULL)
	{
		bsp_seg = (t_bsp_segment *)current->content;
		bsp_seg->segment->data.ceil = ((t_bsp_tree_node_data *)tree_node->data)
			->sector_data.ceil;
		bsp_seg->segment->data.floor = ((t_bsp_tree_node_data *)tree_node->data)
			->sector_data.floor;
		if (bsp_seg->segment->data.type == PORTAL)
		{
			bsp_seg->segment->data.data.portal.destination = ((t_bsp_segment *)
					bsp_seg->segment->data.data.portal.destination)->segment;
			bsp_seg->segment->data.data.portal.tree_node_ptr = tree_node;
			bsp_seg->segment->data.data.portal.dijkstra_id = -1;
		}
		current = current->next;
	}
}

void	tree_update_portals_links_to_segments(t_tree_node *tree)
{
	if (tree->left == NULL && tree->right == NULL)
	{
		lst_update_portals_links_to_segments(
			&((t_bsp_tree_node_data*)tree->data)->sector_segments, tree);
		return ;
	}
	tree_update_portals_links_to_segments(tree->left);
	tree_update_portals_links_to_segments(tree->right);
}
