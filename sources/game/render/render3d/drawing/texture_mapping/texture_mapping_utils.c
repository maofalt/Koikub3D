/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:04:34 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/11 02:20:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "ressources_managers.h"
#include "structures.h"
#include <assert.h>

double	calc_wall_texture_repeat_factor_x(t_segment_d *segment)
{
	return (segment->data.size / 8);
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

void	texture_mapping_calc_u(t_texture_mapping_data *data)
{
	double		relative_segment_width;
	const int	use_y = (fabs(data->clipped_relative_segment.point_b.x
				- data->clipped_relative_segment.point_a.x)
			<= fabs(data->relative_segment.point_a.y
				- data->relative_segment.point_b.y));

	relative_segment_width = data->relative_segment.point_b.vec[use_y]
		- data->relative_segment.point_a.vec[use_y];
	data->u0 = ((data->clipped_relative_segment.point_a.vec[use_y]
				- data->relative_segment.point_a.vec[use_y])
			* data->texture_width
			* data->texture_tiling_factor_x)
		/ relative_segment_width;
	data->u1 = ((data->clipped_relative_segment.point_b.vec[use_y]
				- data->relative_segment.point_a.vec[use_y])
			* data->texture_width
			* data->texture_tiling_factor_x)
		/ relative_segment_width;
	data->u0 += calc_wall_texture_offset(data->surface) * data->texture_width;
	data->u1 += calc_wall_texture_offset(data->surface) * data->texture_width;
}
