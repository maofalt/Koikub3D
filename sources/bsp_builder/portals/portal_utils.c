/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 00:31:41 by olimarti          #+#    #+#             */
/*   Updated: 2023/12/04 05:26:34 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures_utils.h"
#include "maths_utils.h"

t_vector4d	get_segment_max_on_separator(t_bsp_segment *bsp_segment, int use_x)
{
	const int	v_rank = (use_x == 0);
	double		maxi;
	t_vector4d	max_point;

	maxi = -INFINITY;
	if (bsp_segment->has_separator_intersection != 0)
	{
		max_point = point2d_to_vector4d(&bsp_segment->separator_intersection);
		maxi = bsp_segment->separator_intersection.vec[v_rank];
	}
	if (bsp_segment->point_a_side == SIDE_ON
		&& bsp_segment->segment->point_a.vec[v_rank] > maxi)
	{
		max_point = bsp_segment->segment->point_a;
		maxi = max_point.vec[v_rank];
	}
	if (bsp_segment->point_b_side == SIDE_ON
		&& bsp_segment->segment->point_b.vec[v_rank] > maxi)
	{
		max_point = bsp_segment->segment->point_b;
		maxi = max_point.vec[v_rank];
	}
	return (max_point);
}

t_vector4d	get_segment_min_on_separator(t_bsp_segment *bsp_segment, int use_x)
{
	const int	v_rank = (use_x == 0);
	double		mini;
	t_vector4d	min_point;

	mini = INFINITY;
	if (bsp_segment->has_separator_intersection != 0)
	{
		min_point = point2d_to_vector4d(&bsp_segment->separator_intersection);
		mini = fmin(bsp_segment->separator_intersection.vec[v_rank], mini);
	}
	if (bsp_segment->point_a_side == SIDE_ON
		&& bsp_segment->segment->point_a.vec[v_rank] < mini)
	{
		min_point = bsp_segment->segment->point_a;
		mini = min_point.vec[v_rank];
	}
	if (bsp_segment->point_b_side == SIDE_ON
		&& bsp_segment->segment->point_b.vec[v_rank] < mini)
	{
		min_point = bsp_segment->segment->point_b;
		mini = min_point.vec[v_rank];
	}
	return (min_point);
}

static int	comparison_fun_x(
	t_list *bsp_segment_node_a,
	t_list *bsp_segment_node_b
	)
{
	t_bsp_segment	*bsp_segment_a;
	t_bsp_segment	*bsp_segment_b;
	double			min_a;
	double			min_b;

	bsp_segment_a = bsp_segment_node_a->content;
	bsp_segment_b = bsp_segment_node_b->content;
	min_a = get_segment_min_on_separator(bsp_segment_a, 1).x;
	min_b = get_segment_min_on_separator(bsp_segment_b, 1).x;

	return ((min_a > min_b) - (min_a < min_b));
}

static int	comparison_fun_y(
	t_list *bsp_segment_node_a,
	t_list *bsp_segment_node_b
	)
{
	t_bsp_segment	*bsp_segment_a;
	t_bsp_segment	*bsp_segment_b;
	double			min_a;
	double			min_b;

	bsp_segment_a = bsp_segment_node_a->content;
	bsp_segment_b = bsp_segment_node_b->content;
	min_a = get_segment_min_on_separator(bsp_segment_a, 0).y;
	min_b = get_segment_min_on_separator(bsp_segment_b, 0).y;
	return ((min_a > min_b) - (min_a < min_b));
}

void	sort_intersect_segments_array(
				t_list **bsp_segments_nodes_array,
				int size,
				int is_sep_horizontal
				)
{
	if (is_sep_horizontal)
		sort_lst_node_array(bsp_segments_nodes_array, size, comparison_fun_y);
	else
		sort_lst_node_array(bsp_segments_nodes_array, size, comparison_fun_x);
}
