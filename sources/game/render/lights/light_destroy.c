/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 06:00:35 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 06:00:36 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "render_3D.h"
#include "structures.h"
#include "settings.h"
#include "assert.h"

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

void	render_destroy_lights(t_3d_render *render)
{
	light_destroy_all(render);
	sparse_array_destroy(render->lights_data.lights);
	sparse_array_destroy(render->lights_data.lens_flare);
}
