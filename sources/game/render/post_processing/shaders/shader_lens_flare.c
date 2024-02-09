/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_lens_flare.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:20:24 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 00:38:42 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "structures.h"

t_color_64	calc_lens_flare_color(t_color_64 original_color,
		t_light_lens_flare *lens_flare, int x, int y)
{
	double	dist;
	double	attenuation;

	dist = sqrt((lens_flare->screen_pos.x - x) * (lens_flare->screen_pos.x - x)
			+ (lens_flare->screen_pos.y - y) * (lens_flare->screen_pos.y - y));
	attenuation = lens_flare->intensity / (dist);
	original_color.r = original_color.r * (1 - attenuation)
		+ lens_flare->color.r * 255 * (attenuation);
	original_color.g = original_color.g * (1 - attenuation)
		+ lens_flare->color.g * 255 * (attenuation);
	original_color.b = original_color.b * (1 - attenuation)
		+ lens_flare->color.b * 255 * (attenuation);
	return (original_color);
}

t_color_64	shader_camera_lens_flare(t_color_64 original_color, int offset,
		t_3d_render *render)
{
	int const			lens_flare_count = render->lights_data.lens_flare->size;
	const int			x = offset % render->width;
	const int			y = offset / render->width;
	int					i;
	t_light_lens_flare	*lens_flare;

	lens_flare = render->lights_data.lens_flare->buffer;
	i = 0;
	while (i < lens_flare_count)
	{
		if (lens_flare[i].visible)
		{
			original_color = calc_lens_flare_color(original_color,
					&lens_flare[i], x, y);
		}
		++i;
	}
	return (original_color);
}
