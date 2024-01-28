/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_camera_displacement.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 00:36:57 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 03:27:57 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "maths_utils.h"
#include "render_3D.h"
#include "structures.h"
#include <math.h>



// t_point2i	displacement_wave_inv(t_point2i old_pos, t_3d_render *render)
// {
// 	t_point2i	new_pos;
// 	t_point2i	pos;

// 	pos = (t_point2i){{old_pos.x - render->middle.x, old_pos.y
// 		- render->middle.y}};
// 	new_pos.x = cos(pos.y * render->camera->effects.wave.frequency_y
// 			+ render->camera->effects.wave.offset_y + 3.14)
// 		* render->camera->effects.wave.amplitude_y *2 + pos.x + render->middle.x;
// 	new_pos.y = cos(pos.x * render->camera->effects.wave.frequency_x
// 			+ render->camera->effects.wave.offset_x+ 3.14)
// 		* render->camera->effects.wave.amplitude_x + pos.y + render->middle.y;
// 	return (new_pos);
// }

t_color	shader_small_camera_displacement(t_color original_color, int offset,
		t_3d_render *render)
{
	t_point2i	pos;
	int			new_offset;
	t_point2i	new_pos;

	pos = (t_point2i){{offset % render->width, offset / render->width}};
	new_pos = displacement_tilt(pos, render);
	if (render->camera->effects.wave.enabled)
		new_pos = displacement_wave(new_pos, render);
	new_offset = new_pos.y * render->width + new_pos.x;
	if (new_offset >= 0 && new_offset < render->width * render->height
		&& new_pos.x >= 0 && new_pos.x < render->width && new_pos.y >= 0
		&& new_pos.y < render->height)
	{
		original_color = render->buffers.color_bis[new_offset];
		// original_color.r = render->buffers.color_bis[new_offset].r;
		// original_color.g = render->buffers.color_bis[new_offset].g;
	}


	// new_pos = displacement_tilt(pos, render);
	// if (render->camera->effects.wave.enabled)
	// 	new_pos = displacement_wave_inv(new_pos, render);
	// new_offset = new_pos.y * render->width + new_pos.x;
	// if (new_offset >= 0 && new_offset < render->width * render->height
	// 	&& new_pos.x >= 0 && new_pos.x < render->width && new_pos.y >= 0
	// 	&& new_pos.y < render->height)
	// {
	// 	original_color.b = render->buffers.color_bis[new_offset].b;
	// }
	return (original_color);
}
