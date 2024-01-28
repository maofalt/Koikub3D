/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights_visibility.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:04:43 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/28 16:04:43 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "render_3D.h"

static void normalize_vector_3d(t_vector4d *vec)
{
	t_vector4d	product;
	double 		reverse_lenght;

	product.vec = vec->vec;
	product.vec *= product.vec;
	reverse_lenght = 1 / sqrt(product.x + product.y + product.z);
	vec->vec *= reverse_lenght;
}
double dot_product_3d(t_vector4d *a, t_vector4d *b);

void compute_lights_visibility(t_3d_render *render)
{
	int			i;
	t_light		*light;
	t_vector4d	light_pos_screen;
	t_vector4d	camera_light_dir;

	i = render->lights_data.light_count;
	while (i--)
	{
		light = &render->lights_data.lights[i];
		light_pos_screen = transform_camera_relative_point(
				light->pos, render->camera);
		if (light_pos_screen.y > 0)
		{
			light_pos_screen = project_point(render, light_pos_screen);
			if (check_ray_reach_dest(render->camera->pos, light->pos, render))
			{
				if (light->type == DIRECTIONAL_LIGHT)
				{
					camera_light_dir.vec = light->pos.vec - render->camera->pos.vec;
					normalize_vector_3d(&camera_light_dir);
					double cone = dot_product_3d(&camera_light_dir, &light->dir);
						cone = cone * cone * (cone > 0.8);
					render->lights_data.lens_flare[i].intensity = cone;
				}
				else
				{
					render->lights_data.lens_flare[i].intensity = 1;
				}
				render->lights_data.lens_flare[i].screen_pos = light_pos_screen;
				render->lights_data.lens_flare[i].color.d = light->color.d;
				render->lights_data.lens_flare[i].visible = 1;
				continue ;
			}
		}
		render->lights_data.lens_flare[i].visible = 0;
	}
}
