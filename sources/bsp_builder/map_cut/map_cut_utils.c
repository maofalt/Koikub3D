/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:30:36 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 00:44:26 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "draw_utils.h"
#include "maths_utils.h"
#include <assert.h>

void	bsp_segment_compute_intersec(
			t_bsp_segment *segment,
			t_segment_d *separator
			)
{
	segment->point_a_side
		= point_segment_side(separator, &segment->segment->point_a);
	segment->point_b_side
		= point_segment_side(separator, &segment->segment->point_b);
	segment->side_of_separator = segment->point_a_side | segment->point_b_side;
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
	if (segment->side_of_separator == SIDE_ON)
		segment->used_as_separator = 1;
}

int	cut_segment(t_bsp_segment *bsp_segment, t_bsp_segment **new_segment_right)
{
	assert(bsp_segment->side_of_separator == SIDE_INTERSECT);
	(*new_segment_right) = duplicate_bsp_segment(bsp_segment);
	if ((*new_segment_right) == NULL)
		return (1);
	if (bsp_segment->has_separator_intersection)
	{
		if (bsp_segment->point_a_side == SIDE_LEFT)
		{
			bsp_segment->segment->point_b
				= point2d_to_vector4d(&bsp_segment->separator_intersection);
			(*new_segment_right)->segment->point_a
				= point2d_to_vector4d(&bsp_segment->separator_intersection);
		}
		else
		{
			bsp_segment->segment->point_a
				= point2d_to_vector4d(&bsp_segment->separator_intersection);
			(*new_segment_right)->segment->point_b
				= point2d_to_vector4d(&bsp_segment->separator_intersection);
		}
	}
	return (0);
}

int	cut_portal(
	t_bsp_segment *bsp_segment,
	t_bsp_segment **right_portal_1,
	t_bsp_segment **right_portal_2
	)
{
	t_bsp_segment	*linked_segment;

	assert(bsp_segment->side_of_separator == SIDE_INTERSECT);
	linked_segment = bsp_segment->segment->data.data.portal.destination;
	linked_segment->point_a_side = bsp_segment->point_a_side;
	linked_segment->point_b_side = bsp_segment->point_b_side;
	linked_segment->separator_intersection
		= bsp_segment->separator_intersection;
	linked_segment->side_of_separator = bsp_segment->side_of_separator;
	linked_segment->has_separator_intersection
		= bsp_segment->has_separator_intersection;
	linked_segment->used_as_separator = 1;
	if (cut_segment(bsp_segment, right_portal_1))
	{
		return (1);
	}
	if (cut_segment(linked_segment, right_portal_2))
	{
		destroy_full_bsp_segment(*right_portal_1);
		return (1);
	}
	(*right_portal_1)->segment->data.data.portal.destination = *right_portal_2;
	(*right_portal_2)->segment->data.data.portal.destination = *right_portal_1;
	return (0);
}
