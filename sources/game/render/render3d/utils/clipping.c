/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 14:20:40 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 14:20:45 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_utils.h"
#include "render_3D.h"
#include "structures.h"

// TODO maybe use arg instead of define
int	relative_segment_clip_front(t_segment_d *segment)
{
	t_segment_d	horizontal;
	t_vector4d	intersect;

	horizontal = (t_segment_d){.point_a = {{1, CAMERA_PROXIMITY, 0, 0}},
		.point_b = {{10, CAMERA_PROXIMITY, 0, 0}}};
	if (segment->point_a.y <= 0 && segment->point_b.y <= 0)
		return (1);
	if (segment->point_a.y <= CAMERA_PROXIMITY
		|| segment->point_b.y <= CAMERA_PROXIMITY)
	{
		intersect = point2d_to_vector4d_cpy(find_intersection(horizontal,
					*segment));
		intersect.y = CAMERA_PROXIMITY;
		if (segment->point_a.y < CAMERA_PROXIMITY)
		{
			intersect.z = segment->point_a.z;
			segment->point_a = intersect;
		}
		if (segment->point_b.y < CAMERA_PROXIMITY)
		{
			intersect.z = segment->point_b.z;
			segment->point_b = intersect;
		}
	}
	return (0);
}
