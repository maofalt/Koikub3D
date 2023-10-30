/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:30:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/30 15:47:41 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsp_builder.h"
#include "structures.h"

t_bsp_segment	*create_bsp_segment(t_segment_d *segment)
{
	t_bsp_segment	*bsp_seg;

	bsp_seg = malloc(sizeof(t_bsp_segment));
	if (!bsp_seg)
	{
		return (NULL);
	}
	bsp_seg->segment = segment;
	bsp_seg->used_as_separator = 0;
	bsp_seg->side_of_separator = SIDE_ON;
	bsp_seg->point_a_side = SIDE_ON;
	bsp_seg->point_b_side = SIDE_ON;
	bsp_seg->separator_intersection = (t_point2d){{0}};
	return (bsp_seg);
}

void	delete_bsp_segment(void *bsp_seg)
{
	free(bsp_seg);
}

t_list	*convert_to_bsp_segments(t_list *segment_list)
{
	t_list			*bsp_list;
	t_bsp_segment	*bsp_seg;
	t_list			*new_node;

	bsp_list = NULL;
	while (segment_list)
	{
		bsp_seg = create_bsp_segment(segment_list->content);
		if (!bsp_seg)
		{
			ft_lstclear(&bsp_list, delete_bsp_segment);
			return (NULL);
		}
		new_node = ft_lstnew(bsp_seg);
		if (!new_node)
		{
			delete_bsp_segment(bsp_seg);
			ft_lstclear(&bsp_list, delete_bsp_segment);
			return (NULL);
		}
		ft_lstadd_back(&bsp_list, new_node);
		segment_list = segment_list->next;
	}
	return (bsp_list);
}
