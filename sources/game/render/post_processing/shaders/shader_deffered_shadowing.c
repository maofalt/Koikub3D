/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_deffered_shadowing.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:59:49 by olimarti          #+#    #+#             */
/*   Updated: 2024/01/30 18:18:15 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

void	normalize_vector_2d(t_vector4d *vec)
{
	double	reverse_lenght;

	reverse_lenght = 1 / sqrt(vec->x * vec->x + vec->y * vec->y);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
}

static void	normalize_vector_3d(t_vector4d *vec)
{
	double	reverse_lenght;

	reverse_lenght = 1 / sqrt(vec->x * vec->x
			+ vec->y * vec->y + vec->z * vec->z);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

double	dot_product_2d(t_vector4d *vec1, t_vector4d *vec2)
{
	double result = vec1->x * vec2->x + vec1->y * vec2->y;
	return result;
}
double	dot_product_3d(t_vector4d *vec1, t_vector4d *vec2)
{
	double result = vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z;
	return result;
}

int	check_ray_reach_dest(t_vector4d origin, t_vector4d dest, t_3d_render *render);



t_color_64	shader_deferred_shading(t_color_64 original_color, int offset, t_3d_render *render)
{
	t_color_64 lighting = original_color;
	double luminosity = 0.05;
	lighting.r *= luminosity * 0.5;
	lighting.g *= luminosity;
	lighting.b *= luminosity * 3;

	t_vector4d normal = render->buffers.normal[offset];
	t_vector4d world_pos = render->buffers.world_pos[offset];

	if (render->buffers.depth[offset] == 0)
		return original_color;
	for (int i = 0; i < render->lights_data.light_count; i++)
	{
		if (render->lights_data.lights[i].type != POINT_LIGHT)
			continue;
		t_light *light = &render->lights_data.lights[i];
		t_vector4d light_pos = light->pos;
		// world_pos.vec += normal.vec * 0.0001;
		{

			t_vector4d light_dir = {.vec = {0, 0, 0, 0}};
			light_dir.vec = light->pos.vec - world_pos.vec;
			normalize_vector_3d(&light_dir);

			double diffuse = fmax(dot_product_3d(&normal, &light_dir), 0.0);
			double dist = sqrt((light->pos.x - world_pos.x) * (light->pos.x - world_pos.x) + (light->pos.y - world_pos.y) * (light->pos.y - world_pos.y) + (light->pos.z - world_pos.z) * (light_pos.z - world_pos.z));
			double attenuation = 1.0 / (dist);


			lighting.r += original_color.r * fmin(1, diffuse * attenuation * light->color.r);
			lighting.g += original_color.g * fmin(1, diffuse * attenuation * light->color.g);
			lighting.b += original_color.b * fmin(1, diffuse * attenuation * light->color.b);
		}
		// lighting.b += original_color.b * fmin(1, diffuse * attenuation);
	}

	for (int i = 0; i < render->lights_data.light_count; i++)
	{
		if (render->lights_data.lights[i].type != DIRECTIONAL_LIGHT)
			continue;
		t_light *light = &render->lights_data.lights[i];
		t_vector4d light_pos = light->pos;

		world_pos.vec += normal.vec * 0.0001;
		{

			t_vector4d light_dir = {.vec = {0, 0, 0, 0}};
			light_dir.vec = light_pos.vec - world_pos.vec;
			normalize_vector_3d(&light_dir);
			double cone = fmax(dot_product_3d(&light_dir, &light->dir) > 0.8, 0.0);

			double diffuse = fmax(dot_product_3d(&normal, &light_dir), 0.0);
			double dist = sqrt((light_pos.x - world_pos.x) * (light_pos.x - world_pos.x) + (light_pos.y - world_pos.y) * (light_pos.y - world_pos.y) + (light_pos.z - world_pos.z) * (light_pos.z - world_pos.z));

			double attenuation = 1.0 / (dist / 5);

			if (cone && check_ray_reach_dest(world_pos, light_pos, render))
			{

				lighting.r += original_color.r * fmin(1, diffuse * attenuation * cone * light->color.r);
				lighting.g += original_color.g * fmin(1, diffuse * attenuation * cone * light->color.g);
				lighting.b += original_color.b * fmin(1, diffuse * attenuation * cone * light->color.b);
			}
		}
	}

	return lighting;
}
