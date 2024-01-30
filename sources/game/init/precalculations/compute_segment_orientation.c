/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_segment_orientation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:03:24 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 02:20:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

t_vector4d	compute_sector_center(t_bsp_tree_node_data *sector)
{
	t_vector4d	center;
	t_list		*seg_lst;
	t_segment_d	*segment;
	double		count;

	count = 0;
	center = (t_vector4d){{0, 0, 0, 0}};
	seg_lst = sector->sector_segments;
	while (seg_lst)
	{
		segment = seg_lst->content;
		center.vec += segment->point_a.vec;
		center.vec += segment->point_b.vec;
		seg_lst = seg_lst->next;
		count += 2;
	}
	center.vec /= count;
	return (center);
}

static void	orient_segment(t_segment_d *segment, t_vector4d *center)
{
	t_vector4d	tmp;

	if (point_segment_side(segment, center) == SIDE_LEFT)
	{
		tmp = segment->point_a;
		segment->point_a = segment->point_b;
		segment->point_b = tmp;
	}
}

void	compute_segment_orientation(
	__attribute_maybe_unused__ t_game_data *game_data,
	t_segment_d *segment,
	t_bsp_tree_node_data *sector)
{
	t_vector4d	sector_center;

	sector_center = compute_sector_center(sector);
	orient_segment(segment, &sector_center);
}
