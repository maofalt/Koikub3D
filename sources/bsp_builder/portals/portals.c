/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 18:25:47 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:44:28 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures_utils.h"
#include "maths_utils.h"

int	create_intersect_seg_nodes_array(t_list *bsp_segments, t_list ***array)
{
	int		size;
	t_list	*ptr;

	ptr = bsp_segments;
	size = 0;
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
	ptr = bsp_segments;
	size = 0;
	while (ptr)
	{
		if ((((t_bsp_segment *)ptr->content)->side_of_separator == SIDE_ON)
			|| (((t_bsp_segment *)ptr->content)->has_separator_intersection))
			(*array)[size++] = ptr;
		ptr = ptr->next;
	}
	return (size);
}

t_list	*create_portal_alone(
	t_vector4d *point_a,
	t_vector4d *point_b
	)
{
	t_segment_d		segment;
	t_list			*portal;

	portal = create_bsp_segment_node();
	if (portal == NULL)
		return (NULL);
	segment.point_a = *point_a;
	segment.point_b = *point_b;
	segment.data.type = PORTAL;
	segment.data.data.portal.destination = NULL;
	*((t_bsp_segment *)portal->content)->segment = segment;
	((t_bsp_segment *)portal->content)->used_as_separator = 1;
	((t_bsp_segment *)portal->content)->side_of_separator = SIDE_ON;
	((t_bsp_segment *)portal->content)->point_a_side = SIDE_ON;
	((t_bsp_segment *)portal->content)->point_b_side = SIDE_ON;
	return (portal);
}

static void	_find_gap_update_last(
	t_vector4d *last,
	t_bsp_segment *bsp_segment,
	int is_sep_horizontal)
{
	t_vector4d	seg_max;

	seg_max = get_segment_max_on_separator(bsp_segment, !is_sep_horizontal);
	if (seg_max.vec[is_sep_horizontal] > last->vec[is_sep_horizontal])
		*last = seg_max;
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
	t_vector4d		last;
	t_vector4d		current;
	t_list			*portal;

	i = 0;
	bsp_segment = bsp_segments_sorted_array[i]->content;
	last = get_segment_max_on_separator(bsp_segment, !is_sep_horizontal);
	while (i < size && bsp_segments_sorted_array[i])
	{
		bsp_segment = bsp_segments_sorted_array[i]->content;
		current = get_segment_min_on_separator(bsp_segment, !is_sep_horizontal);
		if (current.vec[is_sep_horizontal] > last.vec[is_sep_horizontal])
		{
			portal = create_portal_alone(&last, &current);
			if (portal == NULL)
				return (ft_lstclear(portal_lst, destroy_full_bsp_segment), 1);
			ft_lstadd_front(portal_lst, portal);
		}
		_find_gap_update_last(&last, bsp_segment, is_sep_horizontal);
		++i;
	}
	return (0);
}

int	create_portals(
	t_list *bsp_segments,
	t_segment_d *separator,
	t_list **portal_lst
	)
{
	t_list	**bsp_segments_nodes_array;
	int		size;
	int		err;
	int		is_sep_horizontal;

	is_sep_horizontal = (separator->point_a.x == separator->point_b.x);
	bsp_segments_nodes_array = NULL;
	err = 0;
	size = create_intersect_seg_nodes_array(bsp_segments,
			&bsp_segments_nodes_array);
	if (bsp_segments_nodes_array == NULL)
		return (1);
	printf("is sep horizontal:%i\n", is_sep_horizontal);
	sort_intersect_segments_array(
		bsp_segments_nodes_array, size, is_sep_horizontal);
	err = find_gaps(bsp_segments_nodes_array, size, is_sep_horizontal,
			portal_lst);
	free(bsp_segments_nodes_array);
	return (err);
}
