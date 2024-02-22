/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_segment_orientation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:03:24 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/12 00:30:05 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

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
	orient_segment(segment, &sector->sector_data.center);
}
