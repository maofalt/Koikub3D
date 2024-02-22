/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 02:21:16 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 05:57:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "game_loop.h"

// UTILS
// TODO move this to a separate file
static double	point_space_partitioning_v4d(
		t_segment_d *separator,
		t_vector4d *point)
{
	t_vector4d	ab;
	t_vector4d	ap;

	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = point->vec - separator->point_a.vec;
	return (ab.x * ap.y - ab.y * ap.x);
}

static t_tree_node	*bsp_search_point_fast(t_tree_node *tree, t_vector4d *point)
{
	t_tree_node	*child;
	double		point_side;

	if (!tree || !tree->left || !tree->right)
		return (tree);
	point_side = point_space_partitioning_v4d(
			&((t_bsp_tree_node_data *)tree->data)->separator, point);
	if (point_side > 0)
		child = bsp_search_point_fast(tree->right, point);
	else
		child = bsp_search_point_fast(tree->left, point);
	return (child);
}

//-----------------
bool	player_wall_intersection(
		t_segment_d *segment,
		t_vector4d *player_pos,
		double radius,
		double height)
{
	t_circle	circle;
	double		player_top;
	double		player_bottom;
	bool		can_pass_through_portal;
	t_segment_d	*portal_dest;

	circle.center = *player_pos;
	circle.radius = radius;
	if (!segment_circle_intersection(segment, &circle))
	{
		return (false);
	}
	player_top = player_pos->z + (height / 2);
	player_bottom = player_pos->z - (height / 2);
	if (segment->data.type == PORTAL)
	{
		portal_dest = segment->data.data.portal.destination;
		can_pass_through_portal = ((player_bottom > segment->data.ceil
					&& player_top < segment->data.floor)
				&& (player_bottom > portal_dest->data.ceil
					&& player_top < portal_dest->data.floor));
		return (!(can_pass_through_portal));
	}
	return (true);
}

t_vector4d	bsp_check_player_collision(t_3d_render *render,
		t_vector4d *player_pos, double radius, double height)
{
	t_tree_node				*node;
	t_bsp_tree_node_data	*data;
	t_segment_d				*segment;
	t_list					*seg_list;
	t_vector4d				collision_normal;

	collision_normal = (t_vector4d){{0, 0, 0, 0}};
	node = bsp_search_point_fast(render->map->bsp, player_pos);
	data = node->data;
	seg_list = data->sector_segments;
	collision_normal.z += (data->sector_data.ceil > (player_pos->z
				- (height / 2)));
	collision_normal.z -= data->sector_data.floor < (player_pos->z
			+ (height / 2));
	while (seg_list)
	{
		segment = seg_list->content;
		if (player_wall_intersection(segment, player_pos, radius, height))
		{
			collision_normal.vec += segment->data.normal.vec;
		}
		seg_list = seg_list->next;
	}
	return (collision_normal);
}

//TODO add normlisations
t_collision_info	check_collision_cylinder(
		t_vector4d pos,
		double radius,
		double height,
		t_3d_render *render)
{
	t_collision_info	collision_info;

	collision_info.collision_normal
		= bsp_check_player_collision(render, &pos, radius, height);
	if (collision_info.collision_normal.x != 0
		|| collision_info.collision_normal.y != 0
		|| collision_info.collision_normal.z != 0)
	{
		collision_info.collision = true;
	}
	else
		collision_info.collision = false;
	return (collision_info);
}
