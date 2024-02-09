/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:07:02 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/09 02:08:51 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "settings.h"
#include "assert.h"

static const t_light	g_lights[] = {
	{
	.type = POINT_LIGHT,
	.pos = {.vec = {2, 2, 1, 0}},
	.color = {.r = 1, .g = 1, .b = 1},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 0.5,
	.show_lens_flare = true,
	.use_raycasting = false
},
{
	.type = POINT_LIGHT,
	.pos = {.vec = {20, 20, 1, 0}},
	.color = {.r = 1, .g = 1, .b = 0},
	.dir = {.vec = {0, 0, 0, 0}},
	.intensity = 1,
	.show_lens_flare = true,
	.use_raycasting = false
},
// {
// 	.type = POINT_LIGHT,
// 	.pos = {.vec = {83.573784, 13.590420, 1, 0}},
// 	.color = {.r = 1, .g = 1, .b = 0},
// 	.dir = {.vec = {0, 0, 0, 0}},
// 	.intensity = 0.5,
// 	.show_lens_flare = false,
// 	.use_raycasting = false
// },
// {
// 	.type = POINT_LIGHT,
// 	.pos = {.vec = {15, 8, -4.088479523707859, 0}},
// 	.color = {.r = 0, .g = 0, .b = 1},
// 	.dir = {.vec = {0, 0, 0, 0}},
// 	.intensity = 0.5,
// 	.show_lens_flare = true,
// 	.use_raycasting = false
// },
// {
// 	.type = POINT_LIGHT,
// 	.pos = {.vec = {8.597030255509164, 35,	3.8024089098964993, 0}},
// 	.color = {.r = 1, .g = 0, .b = 0},
// 	.dir = {.vec = {0, 0, 0, 0}},
// 	.intensity = 0.5,
// 	.show_lens_flare = false,
// 	.use_raycasting = false
// },
};


int	light_spawn(t_3d_render *render, t_light default_light)
{
	t_light				*light;
	int					light_id;
	t_light_lens_flare	lens_flare;

	lens_flare.color = default_light.color;
	lens_flare.intensity = default_light.intensity;
	lens_flare.visible = 0;
	lens_flare.screen_pos = (t_vector4d){.vec = {0, 0, 0, 0}};

	light_id = sparse_array_add(render->lights_data.lights, &default_light);
	if (light_id == -1)
		return (-1);
	light = sparse_array_get(render->lights_data.lights, light_id);
	light->id = light_id;
	light->lens_flare_id = sparse_array_add(render->lights_data.lens_flare,
			&lens_flare);
	if (light->lens_flare_id == -1)
	{
		sparse_array_remove(render->lights_data.lights, light_id);
		return (-1);
	}
	return (light_id);
}

int	light_spawn_default(t_3d_render *render)
{
	int				light_id;
	const t_light	default_light = {
		.type = POINT_LIGHT,
		.pos = {.vec = {0, 0, 0, 0}},
		.color = {.r = 1, .g = 1, .b = 1},
		.dir = {.vec = {1, 0, 0, 0}},
		.intensity = 1,
		.use_raycasting = false,
		.show_lens_flare = false,
		.lens_flare_id = -1
	};

	light_id = light_spawn(render, default_light);
	return (light_id);
}


void	light_destroy(t_3d_render *render, int light_id)
{
	t_light	*light;

	light = sparse_array_get(render->lights_data.lights, light_id);
	if (light)
	{
		if (light->lens_flare_id != -1)
			sparse_array_remove(render->lights_data.lens_flare,
				light->lens_flare_id);
		sparse_array_remove(render->lights_data.lights, light_id);
	}
}

void	light_destroy_all(t_3d_render *render)
{
	t_light	*lights;
	int		i;

	if (render->lights_data.lights == NULL)
		return ;
	lights = render->lights_data.lights->buffer;
	i = 0;
	while (i < render->lights_data.lights->size)
	{
		if (lights[i].lens_flare_id != -1)
			sparse_array_remove(render->lights_data.lens_flare,
				lights[i].lens_flare_id);
		++i;
	}
	sparse_array_remove_all(render->lights_data.lights);
}


int	render_init_lights(t_3d_render *render)
{
	const int	light_count = sizeof(g_lights) / sizeof(g_lights[0]);
	int			i;


	render->lights_data.lights = sparse_array_init(sizeof(t_light),
			DEFAULT_LIGHT_ARRAY_SIZE);
	render->lights_data.lens_flare = sparse_array_init(
			sizeof(t_light_lens_flare), DEFAULT_LIGHT_ARRAY_SIZE);

	if (!render->lights_data.lights || !render->lights_data.lens_flare)
	{
		sparse_array_destroy(render->lights_data.lights);
		sparse_array_destroy(render->lights_data.lens_flare);
		return (1);
	}
	assert(light_count <= DEFAULT_LIGHT_ARRAY_SIZE);
	i = 0;
	while (i < light_count)
	{
		light_spawn(render, g_lights[i]);
		++i;
	}
	return (0);
}

void	render_destroy_lights(t_3d_render *render)
{
	light_destroy_all(render);
	sparse_array_destroy(render->lights_data.lights);
	sparse_array_destroy(render->lights_data.lens_flare);
}
