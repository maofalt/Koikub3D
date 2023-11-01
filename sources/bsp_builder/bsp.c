/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 18:54:15 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/31 17:29:49 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"


static t_list	*_get_next_separator(t_list *bsp_segments_lst)
{
	t_bsp_segment	*segment;

	if (bsp_segments_lst == NULL)
		return (NULL);
	segment = bsp_segments_lst->content;
	while (bsp_segments_lst != NULL && segment->used_as_separator != 0)
	{
		bsp_segments_lst = bsp_segments_lst->next;
		segment = bsp_segments_lst->content;
	}
	return (bsp_segments_lst);
}


t_list	*choose_separator(t_list *bsp_segments)
{
	t_list	*ptr1;
	t_list	*ptr2;

	bsp_segments = _get_next_separator(bsp_segments);
	if (bsp_segments == NULL)
		return (NULL);
	ptr1 = bsp_segments;
	ptr2 = bsp_segments;
	while (ptr1 != NULL)
	{
		ptr1 = _get_next_separator(ptr1);
		if (ptr1)
			ptr1 = _get_next_separator(ptr1);
		if (ptr1)
			ptr2 = _get_next_separator(ptr2);
	}
	return (ptr2);
}

void	compute_segments_intersections(
		t_list *bsp_segments,
		t_segment_d *separator
		)
{
	t_bsp_segment	*segment;

	while (bsp_segments != NULL)
	{
		segment = bsp_segments->content;
		bsp_segment_compute_intersec(segment, separator);
		bsp_segments = bsp_segments->next;
	}
}

int	_recursive_map_cut(t_list **bsp_segments, t_tree_node **tree)
{
	t_list			*separator_node;
	t_bsp_segment	*separator;

	separator_node = choose_separator(*bsp_segments);
	if (separator_node == NULL)
		return (0);
	separator = separator_node->content;
	separator->used_as_separator = 1;
	compute_segments_intersections(*bsp_segments, separator->segment);
	//create_portals
	return (0);
}


int	construct_bsp(t_list **segments, t_tree_node **tree)
{
	t_list	*converted_segments;

	converted_segments = convert_to_bsp_segments(*segments);
	if (converted_segments)
		return (1);
	return (0);
}
