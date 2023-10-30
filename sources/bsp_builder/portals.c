/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:25:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/30 23:39:12 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"

int	comparison_fun_x(t_list *bsp_segment_node_a, t_list *bsp_segment_node_b)
{
	t_bsp_segment	*bsp_segment_a;
	t_bsp_segment	*bsp_segment_b;
	double			result;

	bsp_segment_a = bsp_segment_node_a->content;
	bsp_segment_b = bsp_segment_node_b->content;
	result = INFINITY;
	if (bsp_segment_a->point_a_side == SIDE_ON)
		result = fmin(bsp_segment_a->segment->point_a.x, result);
	if (bsp_segment_a->point_b_side == SIDE_ON)
		result = fmin(bsp_segment_a->segment->point_b.x, result);
	if (bsp_segment_b->point_a_side == SIDE_ON)
		result = fmin(bsp_segment_b->segment->point_a.x, result);
	if (bsp_segment_b->point_b_side == SIDE_ON)
		result = fmin(bsp_segment_b->segment->point_b.x, result);
	return (result);
}

int	comparison_fun_y(t_list *bsp_segment_node_a, t_list *bsp_segment_node_b)
{
	t_bsp_segment	*bsp_segment_a;
	t_bsp_segment	*bsp_segment_b;
	double			result;

	bsp_segment_a = bsp_segment_node_a->content;
	bsp_segment_b = bsp_segment_node_b->content;
	result = INFINITY;
	if (bsp_segment_a->point_a_side == SIDE_ON)
		result = fmin(bsp_segment_a->segment->point_a.y, result);
	if (bsp_segment_a->point_b_side == SIDE_ON)
		result = fmin(bsp_segment_a->segment->point_b.y, result);
	if (bsp_segment_b->point_a_side == SIDE_ON)
		result = fmin(bsp_segment_b->segment->point_a.y, result);
	if (bsp_segment_b->point_b_side == SIDE_ON)
		result = fmin(bsp_segment_b->segment->point_b.y, result);
	return (result);
}

int	create_intersect_seg_nodes_array(t_list *bsp_segments, t_list ***array)
{
	int		size;
	t_list	*ptr;

	ptr = bsp_segments;
	while (ptr)
	{
		if ((((t_bsp_segment *)ptr->content)->side_of_separator == SIDE_ON)
			|| (((t_bsp_segment *)ptr->content)->has_separator_intersection))
			++size;
		ptr = ptr->next;
	}
	(*array) = malloc(sizeof(t_list *) * size);
	if (!(*array))
		return (-1);
	size = 0;
	while (bsp_segments)
	{
		if ((((t_bsp_segment *)ptr->content)->side_of_separator == SIDE_ON)
			|| (((t_bsp_segment *)ptr->content)->has_separator_intersection))
			(*array)[size++] = bsp_segments;
		bsp_segments = bsp_segments->next;
	}
	return (size);
}


int	find_gaps(t_list *bsp_segments, int is_sep_horizontal)
{
	t_list	**bsp_segments_nodes_array;
	int		size;

	size = create_intersect_seg_nodes_array(bsp_segments,
			&bsp_segments_nodes_array);
	if (bsp_segments_nodes_array == NULL)
		return (1);

	if (is_sep_horizontal)
		sort_lst_node_array(bsp_segments_nodes_array, size, comparison_fun_y);
	else
		sort_lst_node_array(bsp_segments_nodes_array, size, comparison_fun_x);
	return (0);
}
