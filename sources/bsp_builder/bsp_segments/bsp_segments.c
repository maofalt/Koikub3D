/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp_segments.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 23:30:12 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:50:18 by olimarti         ###   ########.fr       */
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
	bsp_seg->has_separator_intersection = 0;
	bsp_seg->node_ptr = NULL;
	return (bsp_seg);
}

void	destroy_full_bsp_segment(void *bsp_seg)
{
	if (bsp_seg)
	{
		free(((t_bsp_segment *)bsp_seg)->segment);
		free(bsp_seg);
	}
}

t_bsp_segment	*init_new_bsp_segment(void)
{
	t_bsp_segment	*bsp_seg;
	t_segment_d		*seg;

	bsp_seg = malloc(sizeof(t_bsp_segment));
	if (!bsp_seg)
		return (NULL);
	seg = malloc(sizeof(t_segment_d));
	if (!seg)
	{
		free(bsp_seg);
		return (NULL);
	}
	bsp_seg->segment = seg;
	bsp_seg->used_as_separator = 0;
	bsp_seg->side_of_separator = SIDE_ON;
	bsp_seg->point_a_side = SIDE_ON;
	bsp_seg->point_b_side = SIDE_ON;
	bsp_seg->separator_intersection = (t_point2d){{0}};
	bsp_seg->has_separator_intersection = 0;
	bsp_seg->node_ptr = NULL;
	return (bsp_seg);
}

t_bsp_segment	*duplicate_bsp_segment(t_bsp_segment *original)
{
	t_bsp_segment	*dup;
	t_segment_d		*seg_dup;

	if (!original)
		return (NULL);
	dup = malloc(sizeof(t_bsp_segment));
	if (!dup)
		return (NULL);
	seg_dup = malloc(sizeof(t_segment_d));
	if (!seg_dup)
	{
		free(dup);
		return (NULL);
	}
	*seg_dup = *(original->segment);
	dup->segment = seg_dup;
	dup->used_as_separator = original->used_as_separator;
	dup->side_of_separator = original->side_of_separator;
	dup->point_a_side = original->point_a_side;
	dup->point_b_side = original->point_b_side;
	dup->separator_intersection = original->separator_intersection;
	dup->has_separator_intersection = original->has_separator_intersection;
	dup->node_ptr = original->node_ptr;
	return (dup);
}
