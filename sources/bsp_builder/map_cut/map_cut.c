/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:29:39 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/07 22:22:10 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"
#include "maths_utils.h"

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

int	cut_segment_node_wall(
	t_list **bsp_segment_node,
	t_list **left,
	t_list **right)
{
	t_bsp_segment	*bsp_segment;
	t_bsp_segment	*new_segment;
	t_list			*new_node_right;

	bsp_segment = (*bsp_segment_node)->content;
	if (cut_segment(bsp_segment, &new_segment))
	{
		perror("cut_segment_node_wall");
		return (1);
	}
	new_node_right = ft_lstnew(new_segment);
	if (!new_node_right)
		return (destroy_full_bsp_segment(new_segment), 1);
	new_segment->node_ptr = new_node_right;
	ft_lstadd_front(right, new_node_right);
	lst_move_node(left, bsp_segment_node);
	return (0);
}

int	cut_portal_in_node(
	t_bsp_segment *bsp_segment,
	t_list **right_portal_1,
	t_list **right_portal_2
	)
{
	t_bsp_segment	*new_segment_1;
	t_bsp_segment	*new_segment_2;

	if (cut_portal(bsp_segment, &new_segment_1, &new_segment_2))
	{
		perror("cut_segment_node_portal");
		return (1);
	}
	*right_portal_1 = ft_lstnew(new_segment_1);
	if (!*right_portal_1)
	{
		destroy_full_bsp_segment(new_segment_1);
		destroy_full_bsp_segment(new_segment_2);
		return (1);
	}
	*right_portal_2 = ft_lstnew(new_segment_2);
	if (!*right_portal_2)
	{
		destroy_full_bsp_segment(new_segment_2);
		return (1);
	}
	return (0);
}

int	cut_segment_node_portal(
	t_list **bsp_segment_node,
	t_list **left,
	t_list **right
	)
{
	t_bsp_segment	*bsp_segment;
	t_list			*new_segment_1;
	t_list			*new_segment_2;
	t_bsp_segment	*tmp_seg;

	bsp_segment = (*bsp_segment_node)->content;
	if (cut_portal_in_node(bsp_segment, &new_segment_1, &new_segment_2))
		return (1);
	tmp_seg = new_segment_1->content;
	tmp_seg->node_ptr = new_segment_1;
	ft_lstadd_front(right, new_segment_1);

	tmp_seg = new_segment_2->content;
	tmp_seg->node_ptr = new_segment_2;
	ft_lstadd_front(
		&((t_bsp_segment*)bsp_segment->segment->data.data.portal.destination)
		->node_ptr->next, new_segment_2);
	lst_move_node(left, bsp_segment_node);
	return (0);
}

int	cut_segment_to_node(
	t_list **bsp_segment_node,
	t_list **left,
	t_list **right)
{
	t_bsp_segment	*bsp_segment;

	bsp_segment = (*bsp_segment_node)->content;
	if (bsp_segment->segment->data.type == WALL)
	{
		if (cut_segment_node_wall(bsp_segment_node, left, right))
			return (1);
	}
	else
	{
		if (cut_segment_node_portal(bsp_segment_node, left, right))
			return (1);
	}
	return (0);
}
//TODO: rename this function
static int	_map_cut_segment_on(t_list **bsp_segments, t_list **left, t_list **right)
{
	t_list			*new_node_right;

	new_node_right = duplicate_bsp_segment_node(*bsp_segments);
	if (new_node_right == NULL)
		return (1);
	if (((t_bsp_segment *)new_node_right->content)
		->segment->data.type == PORTAL)
	{
		((t_bsp_segment *)new_node_right->content)->segment
			->data.data.portal.destination = (*bsp_segments)->content;
		((t_bsp_segment *)(*bsp_segments)->content)->segment
			->data.data.portal.destination = new_node_right->content;
	}
	ft_lstadd_front(right, new_node_right);
	lst_move_node(left, bsp_segments);
	return (0);
}

int	map_cut(t_list **bsp_segments, t_list **left, t_list **right)
{
	t_bsp_segment	*current;

	while (*bsp_segments)
	{
		current = (*bsp_segments)->content;
		if (current->side_of_separator == SIDE_INTERSECT)
		{
			if (cut_segment_to_node(bsp_segments, left, right))
				return (1);
		}
		else if (current->side_of_separator == SIDE_LEFT)
			lst_move_node(left, bsp_segments);
		else if (current->side_of_separator == SIDE_RIGHT)
			lst_move_node(right, bsp_segments);
		else
		{
			if (_map_cut_segment_on(bsp_segments, left, right))
				return (1);
		}
	}
	return (0);
}
