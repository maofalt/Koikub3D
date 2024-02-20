/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_light_intensity.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 04:07:11 by olimarti          #+#    #+#             */
/*   Updated: 2024/02/20 04:12:19 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_utils.h"
#include "structures.h"
#include "maths_utils.h"
#include "render_3D.h"

//TODO: Put check_ray_reach_dest in header
int	check_ray_reach_dest(
		t_vector4d origin, t_vector4d dest, t_3d_render *render);

static void	_normalize_vector_3d(t_vector4d *vec)
{
	double	reverse_lenght;

	reverse_lenght = 1 / sqrt(vec->x * vec->x
			+ vec->y * vec->y + vec->z * vec->z);
	vec->vec[0] *= reverse_lenght;
	vec->vec[1] *= reverse_lenght;
	vec->vec[2] *= reverse_lenght;
}

double	calc_light_intensity(
	t_3d_render *render,
	const t_light *const light,
	t_vector4d world_pos,
	t_vector4d normal
)
{
	double					intensity;
	t_vector4d				light_dir;
	const t_vector4d *const	light_pos = &light->pos;

	intensity = light->intensity;
	world_pos.vec += normal.vec * 0.001;
	light_dir.vec = light_pos->vec - world_pos.vec;
	_normalize_vector_3d(&light_dir);
	intensity *= calc_light_cone(light, &light_dir);
	intensity *= calc_light_normal_diffuse(&normal, &light_dir);
	intensity *= calc_light_distance_attenuation(light_pos, &world_pos);
	if (light->use_raycasting == false
		|| check_ray_reach_dest(world_pos, *light_pos, render))
	{
		return (intensity);
	}
	return (0);
}
