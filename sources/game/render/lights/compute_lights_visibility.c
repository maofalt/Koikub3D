/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights_visibility.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:04:43 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/27 22:02:52 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "render_3D.h"

static inline double	_dot_product_3d(
	const t_vector4d *const vec1,
	const t_vector4d *const vec2)
{
	return (vec1->x * vec2->x + vec1->y * vec2->y + +vec1->z * vec2->z);
}

static void	normalize_vector_3d(t_vector4d *vec)
{
	t_vector4d	product;
	double		reverse_lenght;

	product.vec = vec->vec;
	product.vec *= product.vec;
	reverse_lenght = 1 / sqrt(product.x + product.y + product.z);
	vec->vec *= reverse_lenght;
}

static double	compute_cone_intensity(
	const t_vector4d *const camera_pos,
	const t_vector4d *const light_pos,
	const t_vector4d *const light_dir)
{
	t_vector4d	camera_light_dir;
	double		cone;

	camera_light_dir.vec = light_pos->vec - camera_pos->vec;
	normalize_vector_3d(&camera_light_dir);
	cone = _dot_product_3d(&camera_light_dir, light_dir);
	cone = cone * cone * (cone > 0.8);
	return (cone);
}

static void	_compute_light_visibility(t_3d_render *render, t_light *light)
{
	t_vector4d					light_pos_screen;
	t_light_lens_flare *const	lens_flare = sparse_array_get(
			render->lights_data.lens_flare, light->lens_flare_id);

	if (lens_flare == NULL)
		return ;
	lens_flare->visible = 0;
	light_pos_screen = transform_camera_relative_point(
			light->pos, render->camera);
	if (light_pos_screen.y <= 0)
		return ;
	light_pos_screen = project_point(render, light_pos_screen);
	if (check_ray_reach_dest(render->camera->pos, light->pos, render))
	{
		if (light->type == DIRECTIONAL_LIGHT)
			lens_flare->intensity = compute_cone_intensity(
					&render->camera->pos, &light->pos, &light->dir);
		else
			lens_flare->intensity = 1;
		lens_flare->screen_pos = light_pos_screen;
		lens_flare->color.d = light->color.d;
		lens_flare->visible = 1;
	}
}

void	compute_lights_visibility(t_3d_render *render)
{
	int			i;
	t_light		*light;

	i = render->lights_data.lights->size;
	while (i--)
	{
		light = render->lights_data.lights->buffer;
		light += i;
		if (light->show_lens_flare)
			_compute_light_visibility(render, light);
	}
}
