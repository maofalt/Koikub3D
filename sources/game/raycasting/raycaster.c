/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:40:01 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 05:42:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "draw_utils.h"
#include "render_3D.h"
#include "maths_utils.h"
#include "raycaster.h"

typedef struct s_ray
{
	t_vector4d	origin;
	t_vector4d	direction;
	t_vector4d	dest;
	double		square_dist;
	t_segment_d	segment_ray;
}	t_ray;

int	ray_segment_intersection_check_height(
	t_segment_d const *segment,
	t_ray *ray)
{
	t_vector4d			normal;
	double				t;
	double				z;
	const t_vector4d	bot_left_surface = {
	{segment->point_a.x, segment->point_a.y, segment->data.ceil, 0}};

	normal = segment->data.normal;
	t = (dot_product_2d(&normal, &bot_left_surface)
			- dot_product_2d(&normal, &ray->origin))
		/ dot_product_2d(&normal, &ray->direction);
	z = ray->origin.z + ray->direction.z * t;
	if (z < segment->data.ceil || z > segment->data.floor)
		return (0);
	segment = segment->data.data.portal.destination;
	normal = segment->data.normal;
	t = (dot_product_2d(&normal, &bot_left_surface)
			- dot_product_2d(&normal, &ray->origin))
		/ dot_product_2d(&normal, &ray->direction);
	z = ray->origin.z + ray->direction.z * t;
	if (z < segment->data.ceil || z > segment->data.floor)
		return (0);
	return (1);
}

static int	ray_segment_intersection(
	t_ray *ray,
	t_segment_d *segment)
{
	t_vector4d			intersection_dir;
	t_point2d			intersection_2d;
	const t_segment_d	*segment_ray = &ray->segment_ray;
	const t_side		point_a_side
		= point_segment_side(segment_ray, &segment->point_a);
	const t_side		point_b_side
		= point_segment_side(segment_ray, &segment->point_b);

	if ((point_a_side != point_b_side))
	{
		intersection_2d = find_intersection_points(
				segment_ray->point_a, segment_ray->point_b,
				segment->point_a, segment->point_b);
		intersection_dir.vec
			= point2d_to_vector4d(&intersection_2d).vec - ray->origin.vec;
		ray->square_dist = intersection_dir.x * intersection_dir.x
			+ intersection_dir.y * intersection_dir.y;
		if (ray_segment_intersection_check_height(segment, ray) == 0)
			return (0);
		return (dot_product_2d(&intersection_dir, &ray->direction) > 0);
	}
	return (0);
}

int	launch_ray(
	t_ray *ray,
	t_tree_node *current_sector_node,
	t_tree_node *dest_node,
	t_list *seg_lst)
{
	t_segment_d	*segment;
	double		last_square_dist;
	int			i;

	i = 0;
	last_square_dist = 0;
	while (seg_lst && ++i < 100000)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL
			&& ray_segment_intersection(ray, segment)
			&& ray->square_dist > last_square_dist)
		{
			current_sector_node = ((t_segment_d *)segment->data.data.portal
					.destination)->data.data.portal.tree_node_ptr;
			seg_lst = ((t_bsp_tree_node_data *)current_sector_node->data)
				->sector_segments;
			last_square_dist = ray->square_dist;
			if (current_sector_node == dest_node)
				return (1);
		}
		else
			seg_lst = seg_lst->next;
	}
	return (0);
}

int	check_ray_reach_dest(
	t_vector4d origin,
	t_vector4d dest,
	t_3d_render *render)
{
	t_ray		ray;
	t_tree_node	*current_sector_node;
	t_list		*seg_lst;
	t_tree_node	*dest_node;

	ray.origin = origin;
	ray.dest = dest;
	ray.direction.vec = dest.vec - origin.vec;
	ray.segment_ray = (t_segment_d){.point_a = ray.origin,
		.point_b = ray.dest};
	current_sector_node = bsp_search_point_fast(render->map->bsp,
			&ray.origin);
	dest_node = bsp_search_point_fast(render->map->bsp,
			&ray.dest);
	if (current_sector_node == dest_node)
	{
		return (1);
	}
	seg_lst = ((t_bsp_tree_node_data *)current_sector_node->data)
		->sector_segments;
	return (launch_ray(&ray, current_sector_node, dest_node, seg_lst));
}
