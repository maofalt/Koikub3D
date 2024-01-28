/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 20:40:01 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/26 20:33:05 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "draw_utils.h"

#include "render_3D.h"


typedef struct s_ray
{
	t_vector4d origin;
	t_vector4d direction;
	t_vector4d dest;

} t_ray;

typedef enum e_side
{
	SIDE_LEFT,
	SIDE_RIGHT,
	SIDE_ON
} t_side;

static t_side
point_segment_side(t_segment_d *separator, t_vector4d *segment_point)
{
	t_vector4d ab;
	t_vector4d ap;
	double cross_product;

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

static double dot_product_2d(t_vector4d *vec1, t_vector4d *vec2)
{
	double result = vec1->x * vec2->x + vec1->y * vec2->y;
	return result;
}

static t_point2d find_intersection(t_segment_d line, t_segment_d seg)
{
	t_point2d intersection;
	t_point2d ab_1;
	t_point2d ab_2;
	double c1;
	double c2;

	ab_1 = (t_point2d){{line.point_b.y - line.point_a.y,
						line.point_a.x - line.point_b.x}};
	c1 = ab_1.x * line.point_a.x + ab_1.y * line.point_a.y;
	ab_2 = (t_point2d){{seg.point_b.y - seg.point_a.y,
						seg.point_a.x - seg.point_b.x}};
	c2 = ab_2.x * seg.point_a.x + ab_2.y * seg.point_a.y;
	intersection.vec = (t_v2d){(ab_2.y * c1 - ab_1.y * c2),
							   (ab_1.x * c2 - ab_2.x * c1)};
	intersection.vec /= ab_1.x * ab_2.y - ab_2.x * ab_1.y;
	return (intersection);
}

static double	point_space_partitioning_v4d(t_segment_d *separator, t_vector4d *point)
{
	t_vector4d	ab;
	t_vector4d	ap;

	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = point->vec - separator->point_a.vec;
	return (ab.x * ap.y - ab.y * ap.x);
}


static t_tree_node	*bsp_search_point_fast(t_tree_node	*tree, t_vector4d *point)
{
	t_tree_node	*child;
	// t_segment_d	separator;
	double		point_side;

	if (!tree || !tree->left || !tree->right)
		return (tree);
	// separator = ;
	point_side = point_space_partitioning_v4d(&((t_bsp_tree_node_data *)tree->data)->separator, point);
	if (point_side > 0)
		child = bsp_search_point_fast(tree->right, point);
	else
		child = bsp_search_point_fast(tree->left, point);
	return (child);
}


// static int ray_segment_intersection(t_ray *ray, t_segment_d *segment)
// {
// 	t_vector4d origin_to_point_a;
// 	t_vector4d origin_to_point_b;

// 	t_segment_d segment_ray = {
// 		.point_a = ray->origin,
// 		.point_b = ray->dest};

// 	t_side point_a_side = point_segment_side(&segment_ray, &segment->point_a);
// 	t_side point_b_side = point_segment_side(&segment_ray, &segment->point_b);

// 	if ((point_a_side != point_b_side))
// 	{
// 		t_vector4d intersection_dir;
// 		t_point2d intersection_2d;

// 		intersection_2d = find_intersection(segment_ray, *segment);
// 		intersection_dir.vec = point2d_to_vector4d(&intersection_2d).vec - ray->origin.vec;

// 		return (dot_product_2d(&intersection_dir, &ray->direction) > 0);
// 	}
// 	return (0);
// }
// static void normalize_vector_3d(t_vector4d *vec)
// {
// 	double reverse_lenght = 1/sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
// 	vec->vec[0] *= reverse_lenght;
// 	vec->vec[1] *= reverse_lenght;
// 	vec->vec[2] *= reverse_lenght;
// }

// public static Vector lineIntersection(Vector planePoint, Vector planeNormal, Vector linePoint, Vector lineDirection) {
//    if (planeNormal.dot(lineDirection.normalize()) == 0) {
//        return null;
//    }

//    double t = (planeNormal.dot(planePoint) - planeNormal.dot(linePoint)) / planeNormal.dot(lineDirection.normalize());
//    return linePoint.plus(lineDirection.normalize().scale(t));
// }


// static void normalize_vector_2d(t_vector4d *vec)
// {
// 	double reverse_lenght = 1/sqrt(vec->x * vec->x + vec->y * vec->y);
// 	vec->vec[0] *= reverse_lenght;
// 	vec->vec[1] *= reverse_lenght;
// }


static int ray_segment_intersection(t_ray *ray, t_segment_d *segment)
{
	t_segment_d segment_ray = {
		.point_a = ray->origin,
		.point_b = ray->dest};

	t_vector4d bot_left_surface =  {{segment->point_a.x, segment->point_a.y, segment->data.ceil, 0}};
	// t_vector4d top_right_surface = {{segment->point_b.x, segment->point_b.y, segment->data.floor, 0}};



	t_side point_a_side = point_segment_side(&segment_ray, &segment->point_a);
	t_side point_b_side = point_segment_side(&segment_ray, &segment->point_b);

	if ((point_a_side != point_b_side))
	{
		t_vector4d intersection_dir;
		t_point2d intersection_2d;

		intersection_2d = find_intersection(segment_ray, *segment);
		intersection_dir.vec = point2d_to_vector4d(&intersection_2d).vec - ray->origin.vec;

		// //calculate Z
		t_vector4d normal = segment->data.normal;
		double t = (dot_product_2d(&normal, &bot_left_surface) - dot_product_2d(&normal, &ray->origin)) / dot_product_2d(&normal, &ray->direction);
		double z = ray->origin.z + ray->direction.z * t;

		if (z < segment->data.ceil || z > segment->data.floor)
			return (0);

		segment = segment->data.data.portal.destination;

		normal = segment->data.normal;
		t = (dot_product_2d(&normal, &bot_left_surface) - dot_product_2d(&normal, &ray->origin)) / dot_product_2d(&normal, &ray->direction);
		z = ray->origin.z + ray->direction.z * t;

		if (z < segment->data.ceil || z > segment->data.floor)
			return (0);


		return (dot_product_2d(&intersection_dir, &ray->direction) > 0);
	}
	return (0);
}

int check_ray_reach_dest(t_vector4d origin, t_vector4d dest, t_3d_render *render)
{
	t_ray ray;
	t_tree_node *current_sector_node;
	t_list *seg_lst;
	t_segment_d *segment;
	t_tree_node *dest_node;
	t_segment_d *last_segment = NULL;

	ray.origin = origin;
	ray.dest = dest;
	ray.direction.vec = dest.vec - origin.vec;
	current_sector_node = bsp_search_point_fast(render->map->bsp,
										   &ray.origin);
	dest_node = bsp_search_point_fast(render->map->bsp,
								 &ray.dest);
	if (current_sector_node == dest_node)
	{
		return (1);
	}
	seg_lst = ((t_bsp_tree_node_data *)current_sector_node->data)->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		if (segment->data.type == PORTAL && ray_segment_intersection(&ray, segment) && segment != last_segment)
		{

			last_segment = segment->data.data.portal.destination;
			current_sector_node = last_segment->data.data.portal.tree_node_ptr;
			seg_lst = ((t_bsp_tree_node_data *)current_sector_node->data)->sector_segments;
			if (current_sector_node == dest_node)
			{
				return (1);
			}
		}
		else
			seg_lst = seg_lst->next;
	}
	return (0);
}
