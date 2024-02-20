/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_deffered_shadowing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:49 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:09:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

void	apply_light_intensity(
	t_color_64 *lighting,
	const t_color_64 *const original_color,
	double const intensity,
	const t_light *const light
)
{
	lighting->r += original_color->r * fmin(1, intensity * light->color.r);
	lighting->g += original_color->g * fmin(1, intensity * light->color.g);
	lighting->b += original_color->b * fmin(1, intensity * light->color.b);
}

t_color_64	shader_deferred_shading(
	t_color_64 original_color,
	int offset,
	t_3d_render *render)
{
	const t_vector4d	normal = render->buffers.normal[offset];
	const t_vector4d	world_pos = render->buffers.world_pos[offset];
	const t_light		*lights = render->lights_data.lights->buffer;
	t_color_64			lighting;
	int					i;

	lighting.r = original_color.r * render->lights_data.ambiant_light.r;
	lighting.g = original_color.g * render->lights_data.ambiant_light.g;
	lighting.b = original_color.b * render->lights_data.ambiant_light.b;
	if (render->buffers.depth[offset] == 0)
		return (original_color);
	i = 0;
	while (i < render->lights_data.lights->size)
	{
		apply_light_intensity(&lighting, &original_color,
			calc_light_intensity(render, &lights[i], world_pos, normal),
			&lights[i]);
		++i;
	}
	return (lighting);
}
