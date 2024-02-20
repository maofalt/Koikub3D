/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 05:31:47 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 05:41:47 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "draw_utils.h"
#include "render_3D.h"

double	dot_product_2d(
	const t_vector4d *const vec1,
	const t_vector4d *const vec2)
{
	const double	result = vec1->x * vec2->x + vec1->y * vec2->y;

	return (result);
}

t_point2d	find_intersection_points(
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

double	point_space_partitioning_v4d(
	t_segment_d *separator,
	t_vector4d *point)
{
	t_vector4d	ab;
	t_vector4d	ap;

	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = point->vec - separator->point_a.vec;
	return (ab.x * ap.y - ab.y * ap.x);
}

t_tree_node	*bsp_search_point_fast(
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
