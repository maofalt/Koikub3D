/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_light_source_logic.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sushi <sushi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:44:41 by sushi             #+#    #+#             */
/*   Updated: 2025/06/24 17:16:55 by sushi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "dynamic_array.h"
#include "game_loop.h"
#include "render_3D.h"
#include "structures.h"
#include "maths_utils.h"
#include "matrix.h"

static void	_light_flicker_effect(
	t_entity_torch_data *data,
	t_light *light,
	t_game_data *game_data)
{
	if (game_data->state.time_since_start
		> data->current_interval_duration + data->last_flicker_time)
	{
		data->last_flicker_time = game_data->state.time_since_start;
		data->flicker_remaining_duration = data->flicker_duration
			+ random_double_xorshift32() * data->flicker_duration_variance;
		data->current_interval_duration = data->flicker_interval
			+ data->flicker_interval
			* data->flicker_interval_variance
			* (random_double_xorshift32() - 0.5);
	}
	if (data->flicker_remaining_duration > 0)
	{
		light->intensity = fmin(fmax(0, light->intensity
					+ data->flicker_intensity_variance
					* (random_double_xorshift32() - 0.5)), 1);
		data->flicker_remaining_duration -= game_data->state.delta_time;
		if (data->flicker_remaining_duration <= 0)
		{
			light->intensity = data->light_intensity;
		}
	}
}

static void	_update_position(
	t_entity *self,
	t_light *light,
	t_3d_render *render)
{
	const double	angle_scale = 0.1;
	double			angle_movement;
	t_matrix3x3		transformation;
	t_point2d		rotated_dir;

	angle_movement = angle_scale * 1.0;
	transformation = rotation_matrix(angle_movement);
	rotated_dir = matrix_vector_multiply(transformation,
			vector4d_to_point2d(&self->physics.dir));
	self->physics.dir = point2d_to_vector4d(&rotated_dir);
	self->physics.dir.z = self->physics.dir.x;
	self->physics.right = self->physics.dir;
	self->physics.right.x = -self->physics.dir.y;
	self->physics.right.y = self->physics.dir.x;
	light->pos = self->physics.pos;
	light->dir = self->physics.dir;
}

static void	_update_flickering_params(
	t_entity *self,
	t_entity_torch_data *data,
	t_game_data *game_data)
{
	data->flicker_interval = 1000;
	if (data->flicker_interval
		* (1 + data->flicker_interval_variance)
		<= data->current_interval_duration)
	{
		data->current_interval_duration = data->flicker_interval;
	}
}

void	entity_light_source_update(t_entity *self, t_game_data *game_data)
{
	t_entity_torch_data	*data;
	t_3d_render			*render;
	t_light				*light;

	data = self->data;
	render = &game_data->game_view_render;
	light = sparse_array_get(render->lights_data.lights,
			data->light_id);
	_update_position(self, light, render);
	_update_flickering_params(self, data, game_data);
	_light_flicker_effect(data, light, game_data);
}
