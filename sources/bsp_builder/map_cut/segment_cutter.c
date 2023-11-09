/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_cutter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:08:44 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:44:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"
#include "maths_utils.h"
#include "structures_utils.h"
#include <assert.h>

static int	cut_segment_node_wall(
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

static int	cut_portal_in_node(
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

static int	cut_segment_node_portal(
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
