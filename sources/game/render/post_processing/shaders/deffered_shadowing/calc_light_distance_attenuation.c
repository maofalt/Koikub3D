/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_distance_attenuation.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:03:21 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:03:24 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

double	calc_light_distance_attenuation(
	const t_vector4d *const light_pos,
	const t_vector4d *const world_pos)
{
	const double	dist
		= sqrt((light_pos->x - world_pos->x)
			* (light_pos->x - world_pos->x)
			+ (light_pos->y - world_pos->y)
			* (light_pos->y - world_pos->y)
			+ (light_pos->z - world_pos->z)
			* (light_pos->z - world_pos->z));
	const double	attenuation = 1.0 / (dist);

	return (attenuation);
}
