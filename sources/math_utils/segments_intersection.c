/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segments_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 01:02:17 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/08 01:59:03 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

t_point2d	find_intersection(t_segment_d line, t_segment_d seg)
{
	t_point2d	intersection;
	t_point2d	ab_1;
	t_point2d	ab_2;
	double		c1;
	double		c2;

	ab_1 = (t_point2d){{line.point_b.y - line.point_a.y,
		line.point_a.x - line.point_b.x}};
	c1 = ab_1.x * line.point_a.x + ab_1.y * line.point_a.y;
	ab_2 = (t_point2d){{seg.point_b.y - seg.point_a.y,
		seg.point_a.x - seg.point_b.x}};
	c2 = ab_2.x * seg.point_a.x + ab_2.y * seg.point_a.y;
	intersection.vec = (t_v2d){(ab_2.y * c1 - ab_1.y * c2),
		(ab_1.x * c2 - ab_2.x * c1)};
	intersection.vec /= ab_1.x * ab_2.y - ab_2.x * ab_1.y;
	return (intersection);
}
