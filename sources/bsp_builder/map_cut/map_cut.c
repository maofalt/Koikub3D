/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:29:39 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/01 16:41:20 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"
#include "draw_utils.h"

#include <assert.h>

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


//TODO: MAYBE relink previous element, when SIDE_ON segment
//		or maybe assert != SIDE_ON
int	map_cut(t_list *bsp_segments, t_list **left, t_list **right)
{
	t_bsp_segment	*current;
	t_list			*new_node_right;

	while (bsp_segments)
	{
		current = bsp_segments->content;
		if (current->side_of_separator == SIDE_INTERSECT)
		{
			if (cut_segment(bsp_segments, &new_node_right))
				return (1);
			new_node_right = ft_lstnew(current);
			if (!new_node_right)
				return (1);
			ft_lstadd_front(right, new_node_right);
			lst_move_node(left, &bsp_segments);
		}
		else if (current->side_of_separator == SIDE_LEFT)
			lst_move_node(left, bsp_segments);
		else if (current->side_of_separator == SIDE_RIGHT)
			lst_move_node(right, bsp_segments);
		else
		{
			new_node_right = duplicate_bsp_segment_node(bsp_segments);
			if (new_node_right)
				return (1);
			ft_lstadd_front(right, new_node_right);
			lst_move_node(left, &bsp_segments);
		}
	}
}
