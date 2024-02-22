/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_math_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:15:12 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/04 22:15:13 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include "structures.h"

double	calc_segment_coef(
			t_segment_d *segment
			)
{
	t_point2d	delta;

	delta.x = segment->point_b.x - segment->point_a.x;
	delta.y = segment->point_b.y - segment->point_a.y;
	assert(delta.x != 0);
	return (delta.y / fabs(delta.x));
}
