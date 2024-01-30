/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:07:02 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/29 20:32:04 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"

static const t_light	g_lights[] = {
{
	.type = DIRECTIONAL_LIGHT,
	.pos = {.vec = {2, 2, 1, 0}},
	.color = {.r = 1, .g = 0, .b = 2},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1,
	.show_lens_flare = true
},
{
	.type = POINT_LIGHT,
	.pos = {.vec = {7, 9.9, 1, 0}},
	.color = {.r = 5, .g = 1, .b = 0},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1,
	.show_lens_flare = true
},
{
	.type = POINT_LIGHT,
	.pos = {.vec = {20, 20, 1, 0}},
	.color = {.r = 5, .g = 1, .b = 0},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1,
	.show_lens_flare = true
},
{
	.type = POINT_LIGHT,
	.pos = {.vec = {83.573784, 13.590420, 1, 0}},
	.color = {.r = 5, .g = 1, .b = 0},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1,
	.show_lens_flare = true
},
{
	.type = POINT_LIGHT,
	.pos = {.vec = {15, 8, -4.088479523707859, 0}},
	.color = {.r = 0, .g = 0, .b = 1},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1, .show_lens_flare = true
},
{
	.type = POINT_LIGHT,
	.pos = {.vec = {8.597030255509164, 35,	3.8024089098964993, 0}},
	.color = {.r = 1, .g = 0, .b = 0},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1,
	.show_lens_flare = true
},
};

void	render_init_lights(t_3d_render *render)
{
	const int	light_count = sizeof(g_lights) / sizeof(g_lights[0]);
	int			i;

	i = 0;
	while (i < light_count)
	{
		render->lights_data.lights[i] = g_lights[i];
		++i;
	}
	render->lights_data.light_count = light_count;
}
