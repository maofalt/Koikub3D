/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:04:34 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/07 03:41:50 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include "structures.h"
#include <assert.h>

double	calc_wall_texture_repeat_factor_x(t_segment_d *segment)
{
	return (segment->data.size) / 8;
}

double	calc_wall_texture_repeat_factor_y(t_segment_d *segment)
{
	return (fabs(segment->data.floor - segment->data.ceil) / 8);
}

double	calc_wall_texture_offset(
	__attribute_maybe_unused__ t_segment_d *segment
	)
{
	return (0);
}
