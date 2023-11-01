/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:25:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/31 17:10:38 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "list_fonctions.h"

t_vector4d	*get_segment_max_on_separator(t_bsp_segment *bsp_segment, int use_x)
{
	const int	v_rank = (use_x == 0);
	int			maxi;
	t_vector4d	*max_point;

	maxi = -INFINITY;
	max_point = NULL;
	if (bsp_segment->has_separator_intersection != 0)
	{
		max_point = &bsp_segment->separator_intersection;
		maxi = bsp_segment->separator_intersection.vec[v_rank];
	}
	if (bsp_segment->point_a_side == SIDE_ON
		&& bsp_segment->segment->point_a.vec[v_rank] > maxi)
	{
		max_point = &bsp_segment->segment->point_a;
		maxi = v_rank;
	}
	if (bsp_segment->point_b_side == SIDE_ON
		&& bsp_segment->segment->point_b.vec[v_rank] > maxi)
	{
		max_point = &bsp_segment->segment->point_b;
		maxi = v_rank;
	}
	return (max_point);
}

t_vector4d	*get_segment_min_on_separator(t_bsp_segment *bsp_segment, int use_x)
{
	const int	v_rank = (use_x == 0);
	int			mini;
	t_vector4d	*min_point;

	mini = INFINITY;
	min_point = NULL;
	if (bsp_segment->has_separator_intersection != 0)
	{
		min_point = &bsp_segment->separator_intersection;
		mini = fmin(bsp_segment->separator_intersection.vec[v_rank], mini);
	}
	if (bsp_segment->point_a_side == SIDE_ON
		&& bsp_segment->segment->point_a.vec[v_rank] < mini)
	{
		min_point = &bsp_segment->segment->point_a;
		mini = v_rank;
	}
	if (bsp_segment->point_b_side == SIDE_ON
		&& bsp_segment->segment->point_b.vec[v_rank] < mini)
	{
		min_point = &bsp_segment->segment->point_b;
		mini = v_rank;
	}
	return (min_point);
}


int	comparison_fun_x(t_list *bsp_segment_node_a, t_list *bsp_segment_node_b)
{
	t_bsp_segment	*bsp_segment_a;
	t_bsp_segment	*bsp_segment_b;
	double			min_a;
	double			min_b;

	bsp_segment_a = bsp_segment_node_a->content;
	bsp_segment_b = bsp_segment_node_b->content;
	min_a = get_segment_min_on_separator(bsp_segment_a, 1)->x;
	min_b = get_segment_min_on_separator(bsp_segment_b, 1)->x;
	return (min_b - min_a);
}

int	comparison_fun_y(t_list *bsp_segment_node_a, t_list *bsp_segment_node_b)
{
	t_bsp_segment	*bsp_segment_a;
	t_bsp_segment	*bsp_segment_b;
	double			min_a;
	double			min_b;

	bsp_segment_a = bsp_segment_node_a->content;
	bsp_segment_b = bsp_segment_node_b->content;
	min_a = get_segment_min_on_separator(bsp_segment_a, 0)->y;
	min_b = get_segment_min_on_separator(bsp_segment_b, 0)->y;
	return (min_b - min_a);
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


t_list	*create_portal_duo(
	t_vector4d *point_a,
	t_vector4d *point_b,
	t_list **portal_a,
	t_list **portal_b
	)
{
	t_segment_d		segment;

	(*portal_a) = create_bsp_segment_node();
	if ((*portal_a))
		return (NULL);
	(*portal_b) = create_bsp_segment_node();
	if ((*portal_b))
		return (free((*portal_a)), NULL);
	segment.point_a = *point_a;
	segment.point_b = *point_b;
	segment.data.type = PORTAL;
	segment.data.data.portal.destination = (*portal_b)->content;
	((t_bsp_segment *)(*portal_a)->content)
		->segment->data.data.portal.destination = point_b;
	segment.data.data.portal.destination = (*portal_a)->content;
	((t_bsp_segment *)(*portal_b)->content)
		->segment->data.data.portal.destination = point_a;
	return (0);
}


int	find_gaps(
	t_list **bsp_segments_sorted_array,
	int size,
	int is_sep_horizontal,
	t_list **portal_lst
	)
{
	int				i;
	t_bsp_segment	*bsp_segment;
	t_vector4d		*last;
	t_vector4d		*current;

	i = 0;
	bsp_segment = bsp_segments_sorted_array[i]->content;
	last = get_segment_min_on_separator(bsp_segment, !is_sep_horizontal);
	while (i < size && bsp_segments_sorted_array[i])
	{
		bsp_segment = bsp_segments_sorted_array[i]->content;
		current = get_segment_min_on_separator(bsp_segment, !is_sep_horizontal);
		if (current->vec[is_sep_horizontal] > last->vec[is_sep_horizontal])
		{

			//gap
			// printf("Gap: ")
		}
		last = get_segment_max_on_separator(bsp_segment, !is_sep_horizontal);
		++i;
	}

}

int	create_portals(t_list *bsp_segments, int is_sep_horizontal)
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

	find_gaps(bsp_segments_nodes_array, size, is_sep_horizontal);
	return (0);
}
