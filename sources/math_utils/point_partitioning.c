/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_partitioning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:30:28 by olimarti          #+#    #+#             */
/*   Updated: 2023/11/03 01:38:40 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structures.h"
#include "maths_utils.h"

double	point_space_partitioning(t_segment_d *separator, t_point2d *point)
{
	t_vector4d	ab;
	t_vector4d	ap;
	t_vector4d	tmp_point;

	tmp_point = point2d_to_vector4d(point);
	ab.vec = separator->point_b.vec - separator->point_a.vec;
	ap.vec = tmp_point.vec - separator->point_a.vec;
	return (ab.x * ap.y - ab.y * ap.x);
}
