/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_post_processing.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:28:17 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/11 02:22:33 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"

static t_color	limit_color(t_color_64 *full_color)
{
	t_color		color;

	color.a = fmin(full_color->a, 255);
	color.r = fmin(full_color->r, 255);
	color.g = fmin(full_color->g, 255);
	color.b = fmin(full_color->b, 255);
	return (color);
}

inline static void	apply_colors_shaders(
	t_color_64 *const color,
	int offset,
	t_3d_render *render
	)
{
	*color = shader_deferred_shading(*color, offset, render);
	*color = shader_camera_lens_flare(*color, offset, render);
	*color = shader_posterization(*color, render);
}

void	game_post_process_frame(t_3d_render *render)
{
	const int	max_offset = render->width * render->height;
	int			i;
	t_color_64	color;

	i = 0;
	compute_lights_visibility(render);
	while (i < max_offset)
	{
		color.a = render->buffers.color[i].a;
		color.r = render->buffers.color[i].r;
		color.g = render->buffers.color[i].g;
		color.b = render->buffers.color[i].b;
		apply_colors_shaders(&color, i, render);
		render->buffers.color_bis[i] = limit_color(&color);
		++i;
	}
	i = 0;
	while (i < max_offset)
	{
		render->buffers.color[i] = render->buffers.color_bis[i];
		render->buffers.color[i] = shader_small_camera_displacement(
				render->buffers.color[i], i, render);
		++i;
	}
}
