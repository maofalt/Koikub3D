/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 01:19:00 by olimarti          #+#    #+#             */
/*   Updated: 2023/10/16 19:53:30 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"

// int	add_dirty_rect(t_canvas *canvas, t_point2d coord, t_point2d size)
// {
// 	t_dirty_rect	*new_dirty_rect;
// 	t_list			*new_node;

// 	new_dirty_rect = (t_dirty_rect *)malloc(sizeof(t_dirty_rect));
// 	if (!new_dirty_rect)
// 		return (1);
// 	new_dirty_rect->pos = coord;
// 	new_dirty_rect->size = size;
// 	new_node = ft_lstnew(new_dirty_rect);
// 	if (!new_node)
// 	{
// 		free(new_dirty_rect);
// 		return (1);
// 	}
// 	return (0);
// }

/*
	Add a drawn segment tto the segments list 
	and mark the area as dirty rectangle
	Codede porrly we have to free all the memory
*/
int	add_segment_to_map(t_canvas *canvas, t_segment_d segment)
{
	t_segment_d	*new_segment;
	t_list		*new_node;
	t_point2d	top_left;
	t_point2d	bottom_right;
	t_point2d	size;

	(void)size;
	new_segment = (t_segment_d *)malloc(sizeof(t_segment_d));
	if (!new_segment)
		return (0);
	*new_segment = segment;
	new_node = ft_lstnew((void *)new_segment);
	if (!new_node)
		return (free(new_segment),
			ft_lstclear(&canvas->segments, free), 1);
	ft_lstadd_back(&(canvas->segments), new_node);
	top_left = (t_point2d){{
		fmin(segment.point_a.x, segment.point_b.x),
		fmin(segment.point_a.y, segment.point_b.y)}};
	bottom_right = (t_point2d){{
		fmax(segment.point_a.x, segment.point_b.x),
		fmax(segment.point_a.y, segment.point_b.y)}};
	size = (t_point2d){{
		bottom_right.x - top_left.x,
		bottom_right.y - top_left.y}};
	return (0);
}
