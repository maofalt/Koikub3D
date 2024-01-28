/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   displacement_wave_effect.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 01:12:13 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 01:13:02 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths_utils.h"
#include "structures.h"
#include <math.h>

t_point2i	displacement_wave(t_point2i old_pos, t_3d_render *render)
{
	t_point2i	new_pos;
	t_point2i	pos;

	pos = (t_point2i){{old_pos.x - render->middle.x, old_pos.y
		- render->middle.y}};
	new_pos.x = cos(pos.y * render->camera->effects.wave.frequency_y
			+ render->camera->effects.wave.offset_y)
		* render->camera->effects.wave.amplitude_y + pos.x + render->middle.x;
	new_pos.y = cos(pos.x * render->camera->effects.wave.frequency_x
			+ render->camera->effects.wave.offset_x)
		* render->camera->effects.wave.amplitude_x + pos.y + render->middle.y;
	return (new_pos);
}
