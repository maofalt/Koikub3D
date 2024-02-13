/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_sector_center.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 00:29:23 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/12 00:33:51 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

void	compute_sector_center(t_bsp_tree_node_data *sector)
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
	sector->sector_data.center = center;
}
