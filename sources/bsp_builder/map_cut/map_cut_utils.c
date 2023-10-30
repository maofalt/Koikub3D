/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:30:36 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/30 20:45:39 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "bsp_builder.h"
#include "draw_utils.h"

void	lst_move_node(t_list **list, t_list **node)
{
	t_list	*next_tmp;

	next_tmp = (*node)->next;
	ft_lstadd_front(list, (*node));
	(*node) = next_tmp;
}

t_side	point_segment_side(t_segment_d *separator, t_vector4d *segment_point)
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


t_point2d	find_intersection(t_segment_d line, t_segment_d seg)
{
	t_point2d	intersection;
	t_point2d	ab_1;
	t_point2d	ab_2;
	double		c1;
	double		c2;

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

void	bsp_segment_compute_intersec(
			t_bsp_segment *segment,
			t_segment_d *separator
			)
{
	segment->point_a_side
		= point_segment_side(separator, &segment->segment->point_a);
	segment->point_b_side
		= point_segment_side(separator, &segment->segment->point_b);
	segment->side_of_separator = segment->point_a_side | segment->point_a_side;
	if (segment->point_a_side != segment->point_b_side)
	{
		segment->separator_intersection
			= find_intersection(*separator, *segment->segment);
		segment->has_separator_intersection = 1;
	}
	else
	{
		segment->has_separator_intersection = 0;
	}

}


