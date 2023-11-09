/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cut.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:29:39 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:44:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"
#include "maths_utils.h"
#include "structures_utils.h"
#include <assert.h>

static int	_map_cut_segment_on(
	t_list **bsp_segments,
	t_list **left,
	t_list **right)
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
