/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:40:01 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 02:35:54 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "draw_utils.h"

#include "render_3D.h"


typedef struct s_ray
{
	t_vector4d	origin;
	t_vector4d	direction;
	t_vector4d	dest;
	double		square_dist;
	t_segment_d	segment_ray;
}	t_ray;


static t_side	_point_segment_side(
	const t_segment_d *const separator,
	const t_vector4d *const segment_point)
{
	t_vector4d	ab;
	t_vector4d	ap;
	double		cross_product;

	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = segment_point->vec - separator->point_a.vec;
	cross_product = ab.x * ap.y - ab.y * ap.x;
	if (cross_product > 0)
		return (SIDE_RIGHT);
	else if (cross_product < 0)
		return (SIDE_LEFT);
	else
		return (SIDE_ON);
}

static double	_dot_product_2d(
	const t_vector4d *const vec1,
	const t_vector4d *const vec2)
{
	const double	result = vec1->x * vec2->x + vec1->y * vec2->y;

	return (result);
}

// static t_point2d	find_intersection(t_segment_d line, t_segment_d seg)
// {
// 	t_point2d	intersection;
// 	t_point2d	ab_1;
// 	t_point2d	ab_2;
// 	double		c1;
// 	double		c2;

// 	ab_1 = (t_point2d){{line.point_b.y - line.point_a.y,
// 		line.point_a.x - line.point_b.x}};
// 	c1 = ab_1.x * line.point_a.x + ab_1.y * line.point_a.y;
// 	ab_2 = (t_point2d){{seg.point_b.y - seg.point_a.y,
// 		seg.point_a.x - seg.point_b.x}};
// 	c2 = ab_2.x * seg.point_a.x + ab_2.y * seg.point_a.y;
// 	intersection.vec = (t_v2d){(ab_2.y * c1 - ab_1.y * c2),
// 		(ab_1.x * c2 - ab_2.x * c1)};
// 	intersection.vec /= ab_1.x * ab_2.y - ab_2.x * ab_1.y;
// 	return (intersection);
// }

static t_point2d	find_intersection_points(
	t_vector4d const line_point_a,
	t_vector4d const line_point_b,
	t_vector4d const seg_a,
	t_vector4d const seg_b)
{
	t_point2d	intersection;
	t_point2d	ab_1;
	t_point2d	ab_2;
	double		c1;
	double		c2;

	ab_1 = (t_point2d){{line_point_b.y - line_point_a.y,
		line_point_a.x - line_point_b.x}};
	c1 = ab_1.x * line_point_a.x + ab_1.y * line_point_a.y;
	ab_2 = (t_point2d){{seg_b.y - seg_a.y,
		seg_a.x - seg_b.x}};
	c2 = ab_2.x * seg_a.x + ab_2.y * seg_a.y;
	intersection.vec = (t_v2d){(ab_2.y * c1 - ab_1.y * c2),
		(ab_1.x * c2 - ab_2.x * c1)};
	intersection.vec /= ab_1.x * ab_2.y - ab_2.x * ab_1.y;
	return (intersection);
}

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


static t_tree_node	*bsp_search_point_fast(
	t_tree_node	*tree,
	t_vector4d *point)
{
	t_tree_node	*child;
	double		point_side;

	if (!tree)
		return (tree);
	point_side = point_space_partitioning_v4d(
			&((t_bsp_tree_node_data *)tree->data)->separator, point);
	if (point_side > 0)
		child = bsp_search_point_fast(tree->right, point);
	else
		child = bsp_search_point_fast(tree->left, point);
	if (child == NULL)
		return (tree);
	return (child);
}


static int ray_segment_intersection(
	t_ray *ray,
	t_segment_d *segment)
{
	const t_segment_d	*segment_ray = &ray->segment_ray;

	const t_side		point_a_side
		= _point_segment_side(segment_ray, &segment->point_a);
	const t_side		point_b_side
		= _point_segment_side(segment_ray, &segment->point_b);

	if ((point_a_side != point_b_side))
	{
		t_vector4d		intersection_dir;
		t_point2d		intersection_2d;

		intersection_2d = find_intersection_points(
			segment_ray->point_a, segment_ray->point_b,
			segment->point_a, segment->point_b);
		intersection_dir.vec = point2d_to_vector4d(&intersection_2d).vec - ray->origin.vec;
		ray->square_dist = intersection_dir.x * intersection_dir.x + intersection_dir.y * intersection_dir.y;

			const t_vector4d	bot_left_surface = {
	{segment->point_a.x, segment->point_a.y, segment->data.ceil, 0}};
		t_vector4d		normal = segment->data.normal;
		double t = (_dot_product_2d(&normal, &bot_left_surface)
				- _dot_product_2d(&normal, &ray->origin))
			/ _dot_product_2d(&normal, &ray->direction);
		double z = ray->origin.z + ray->direction.z * t;

		if (z < segment->data.ceil || z > segment->data.floor)
			return (0);

		segment = segment->data.data.portal.destination;

		normal = segment->data.normal;
		t = (_dot_product_2d(&normal, &bot_left_surface) - _dot_product_2d(&normal, &ray->origin)) / _dot_product_2d(&normal, &ray->direction);
		z = ray->origin.z + ray->direction.z * t;

		if (z < segment->data.ceil || z > segment->data.floor)
			return (0);

		return (_dot_product_2d(&intersection_dir, &ray->direction) > 0);
	}
	return (0);
}


int	lunch_ray(
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

int check_ray_reach_dest(t_vector4d origin, t_vector4d dest, t_3d_render *render)
{
	t_ray ray;
	t_tree_node *current_sector_node;
	t_list *seg_lst;
	t_tree_node *dest_node;

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
	seg_lst = ((t_bsp_tree_node_data *)current_sector_node->data)->sector_segments;
	return (lunch_ray(&ray, current_sector_node, dest_node, seg_lst));
}
